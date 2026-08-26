define_property(GLOBAL PROPERTY BOLT_COVERAGE_INTERFACE_TARGET
    BRIEF_DOCS "Interface target whose consumers are instrumented for coverage"
    FULL_DOCS "Set by bolt_register_for_coverage(). The deferred coverage target creation discovers all EXECUTABLE targets that link to this interface target."
)

function(bolt_register_for_coverage interface_target)
    if(NOT TARGET "${interface_target}")
        message(FATAL_ERROR "bolt_register_for_coverage: target '${interface_target}' does not exist.")
    endif()

    set_property(GLOBAL PROPERTY BOLT_COVERAGE_INTERFACE_TARGET "${interface_target}")
endfunction()

function(_bolt_collect_all_targets dir result_var)
    get_property(targets DIRECTORY "${dir}" PROPERTY BUILDSYSTEM_TARGETS)
    get_property(subdirs DIRECTORY "${dir}" PROPERTY SUBDIRECTORIES)

    foreach(subdir IN LISTS subdirs)
        _bolt_collect_all_targets("${subdir}" subdir_targets)
        list(APPEND targets ${subdir_targets})
    endforeach()

    set("${result_var}" "${targets}" PARENT_SCOPE)
endfunction()

function(_bolt_find_executables_linking_to interface_target result_var)
    set(names_to_check "${interface_target}" "bolt::${interface_target}")

    _bolt_collect_all_targets("${CMAKE_SOURCE_DIR}" all_targets)

    set(executables "")
    foreach(target IN LISTS all_targets)
        get_target_property(type "${target}" TYPE)

        if(NOT type STREQUAL "EXECUTABLE")
            continue()
        endif()

        get_target_property(link_libs "${target}" LINK_LIBRARIES)

        if(NOT link_libs)
            continue()
        endif()

        foreach(check_name IN LISTS names_to_check)
            if("${check_name}" IN_LIST link_libs)
                list(APPEND executables "${target}")
                break()
            endif()
        endforeach()
    endforeach()

    set("${result_var}" "${executables}" PARENT_SCOPE)
endfunction()

function(_bolt_create_coverage_target)
    get_property(interface_target GLOBAL PROPERTY BOLT_COVERAGE_INTERFACE_TARGET)
    
    if(NOT interface_target)
        message(WARNING "[BOLT] No interface target registered via bolt_register_for_coverage(). Skipping coverage target creation.")
        return()
    endif()

    _bolt_find_executables_linking_to("${interface_target}" coverage_targets)

    if(NOT coverage_targets)
        message(WARNING "[BOLT] No executable targets linking to '${interface_target}' found. Skipping coverage target creation.")
        return()
    endif()

    set(coverage_dir "${CMAKE_BINARY_DIR}/coverage")

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        _bolt_create_llvm_coverage_target("${coverage_dir}" "${coverage_targets}")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        _bolt_create_gnu_coverage_target("${coverage_dir}" "${coverage_targets}")
    endif()
endfunction()

function(_bolt_create_llvm_coverage_target coverage_dir coverage_targets)
    string(REGEX MATCH "^[0-9]+" _llvm_major "${CMAKE_CXX_COMPILER_VERSION}")

    find_program(LLVM_PROFDATA_EXECUTABLE
        NAMES "llvm-profdata-${_llvm_major}" llvm-profdata
        REQUIRED
    )

    find_program(LLVM_COV_EXECUTABLE
        NAMES "llvm-cov-${_llvm_major}" llvm-cov
        REQUIRED
    )

    set(profraw_dir "${coverage_dir}/llvm")
    set(profdata_file "${profraw_dir}/coverage.profdata")
    set(html_dir "${profraw_dir}/html")
    set(lcov_file "${profraw_dir}/coverage.lcov")

    list(GET coverage_targets 0 first_target)
    set(remaining_targets "${coverage_targets}")
    list(REMOVE_AT remaining_targets 0)

    set(llvm_cov_binary_args "$<TARGET_FILE:${first_target}>")

    foreach(extra_target IN LISTS remaining_targets)
        list(APPEND llvm_cov_binary_args "-object" "$<TARGET_FILE:${extra_target}>")
    endforeach()

    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E rm -rf "${profraw_dir}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${profraw_dir}"
        COMMAND ${CMAKE_COMMAND} -E env
            "LLVM_PROFILE_FILE=${profraw_dir}/%p.profraw"
            ${CMAKE_CTEST_COMMAND} --test-dir "${CMAKE_BINARY_DIR}" --output-on-failure
        COMMAND ${CMAKE_COMMAND}
            "-DLLVM_PROFDATA_EXECUTABLE=${LLVM_PROFDATA_EXECUTABLE}"
            "-DPROFRAW_DIR=${profraw_dir}"
            "-DPROFDATA_FILE=${profdata_file}"
            -P "${CMAKE_SOURCE_DIR}/cmake/scripts/llvm_merge_profdata.cmake"
        COMMAND ${LLVM_COV_EXECUTABLE} show
            ${llvm_cov_binary_args}
            "-instr-profile=${profdata_file}"
            "-format=html"
            "-output-dir=${html_dir}"
            "${CMAKE_SOURCE_DIR}/src"
            "${CMAKE_SOURCE_DIR}/include"
        COMMAND ${CMAKE_COMMAND}
            "-DLLVM_COV_EXECUTABLE=${LLVM_COV_EXECUTABLE}"
            "-DBINARY_ARGS=${llvm_cov_binary_args}"
            "-DPROFDATA_FILE=${profdata_file}"
            "-DSRC_DIR=${CMAKE_SOURCE_DIR}/src"
            "-DINCLUDE_DIR=${CMAKE_SOURCE_DIR}/include"
            "-DLCOV_FILE=${lcov_file}"
            -P "${CMAKE_SOURCE_DIR}/cmake/scripts/llvm_export_lcov.cmake"
        DEPENDS ${coverage_targets}
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        COMMENT "Generating LLVM code coverage report in ${html_dir}"
        VERBATIM
    )
endfunction()

function(_bolt_create_gnu_coverage_target coverage_dir coverage_targets)
    find_program(LCOV_EXECUTABLE lcov REQUIRED)
    find_program(GENHTML_EXECUTABLE genhtml REQUIRED)

    set(lcov_file "${coverage_dir}/gnu/coverage.lcov")
    set(html_dir "${coverage_dir}/gnu/html")

    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E make_directory "${coverage_dir}/gnu"
        COMMAND ${LCOV_EXECUTABLE} --zerocounters --directory "${CMAKE_BINARY_DIR}"
        COMMAND ${CMAKE_CTEST_COMMAND} --test-dir "${CMAKE_BINARY_DIR}" --output-on-failure
        COMMAND ${LCOV_EXECUTABLE}
            --capture
            --directory "${CMAKE_BINARY_DIR}"
            --base-directory "${CMAKE_SOURCE_DIR}"
            --no-external
            --output-file "${lcov_file}"
        COMMAND ${GENHTML_EXECUTABLE}
            "${lcov_file}"
            --output-directory "${html_dir}"
        DEPENDS ${coverage_targets}
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        COMMENT "Generating GNU code coverage report in ${html_dir}"
        VERBATIM
    )
endfunction()
