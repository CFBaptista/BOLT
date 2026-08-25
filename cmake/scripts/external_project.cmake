function(provide_dependency DEPENDENCY_NAME GIT_REPOSITORY GIT_TAG CMAKE_ARGUMENT_LIST USE_SYSTEM_VERSION)
    set(_need_build FALSE)

    # Determine if we must use system, vendored, or try auto
    if(${USE_SYSTEM_VERSION} STREQUAL "ON")
        find_package(${DEPENDENCY_NAME} CONFIG REQUIRED)

    elseif(${USE_SYSTEM_VERSION} STREQUAL "OFF")
        set(_need_build TRUE)

    else()
        find_package(${DEPENDENCY_NAME} CONFIG QUIET)
        if(NOT "${${DEPENDENCY_NAME}_FOUND}")
            set(_need_build TRUE)
        endif()
    endif()

    # Build the external project if needed
    if(_need_build)
        build_external_project(
            ${DEPENDENCY_NAME}
            ${GIT_REPOSITORY}
            ${GIT_TAG}
            "${CMAKE_ARGUMENT_LIST}"
        )

        find_package(${DEPENDENCY_NAME} CONFIG REQUIRED
            PATHS "${CMAKE_BINARY_DIR}/_external_projects/${DEPENDENCY_NAME}-install"
            NO_DEFAULT_PATH
        )
    endif()

    # Expose local install directory to find_package
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" PARENT_SCOPE)
    set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE)

    # Expose whether we built the dependency
    set(BUILD_${DEPENDENCY_NAME} ${_need_build} PARENT_SCOPE)
endfunction()

function(build_external_project DEPENDENCY_NAME GIT_REPOSITORY GIT_TAG CMAKE_ARGUMENT_LIST)
    # Define paths for the external project
    set(DEPENDENCY_ROOT "${CMAKE_BINARY_DIR}/_external_projects")
    set(DEPENDENCY_SOURCE "${DEPENDENCY_ROOT}/${DEPENDENCY_NAME}-src")
    set(DEPENDENCY_BINARY "${DEPENDENCY_ROOT}/${DEPENDENCY_NAME}-build")
    set(DEPENDENCY_INSTALL "${DEPENDENCY_ROOT}/${DEPENDENCY_NAME}-install")

    message(STATUS "Building ${DEPENDENCY_NAME}...")

    # Download external project if not already present
    if(NOT EXISTS "${DEPENDENCY_SOURCE}/CMakeLists.txt")
        execute_process(
            COMMAND git clone --depth 1 --branch ${GIT_TAG} -c advice.detachedHead=false ${GIT_REPOSITORY} "${DEPENDENCY_SOURCE}"
            RESULT_VARIABLE git_clone_result_code
        )
        if(NOT git_clone_result_code EQUAL 0)
            message(FATAL_ERROR "Failed to clone dependency ${DEPENDENCY_NAME}")
        endif()
    endif()

    # Define cached variables forwarded from parent project
    set(FORWARDED_ARGUMENT_LIST "")

    # Forward CMake variables from parent project to external project
    if(CMAKE_CXX_COMPILER)
        list(APPEND FORWARDED_ARGUMENT_LIST "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")
    endif()
    if(CMAKE_C_COMPILER)
        list(APPEND FORWARDED_ARGUMENT_LIST "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}")
    endif()
    if(CMAKE_LINKER)
        list(APPEND FORWARDED_ARGUMENT_LIST "-DCMAKE_LINKER=${CMAKE_LINKER}")
    endif()
    if(CMAKE_GENERATOR)
        list(APPEND FORWARDED_ARGUMENT_LIST "-G${CMAKE_GENERATOR}")
    endif()

    # Configure external project
    execute_process(
        COMMAND ${CMAKE_COMMAND}
            -S "${DEPENDENCY_SOURCE}"
            -B "${DEPENDENCY_BINARY}"
            -DCMAKE_BUILD_TYPE=Release
            -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_INSTALL}
            ${FORWARDED_ARGUMENT_LIST}
            ${CMAKE_ARGUMENT_LIST}
        RESULT_VARIABLE cmake_configure_result_code
    )
    if(NOT cmake_configure_result_code EQUAL 0)
        message(FATAL_ERROR "Failed to configure dependency ${DEPENDENCY_NAME}")
    endif()

    # Build and install external project
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build "${DEPENDENCY_BINARY}" --target install
        RESULT_VARIABLE cmake_build_result_code
    )
    if(NOT cmake_build_result_code EQUAL 0)
        message(FATAL_ERROR "Failed to build or install dependency ${DEPENDENCY_NAME}")
    endif()

    # Expose local install directory to find_package
    list(APPEND CMAKE_PREFIX_PATH "${DEPENDENCY_INSTALL}")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" PARENT_SCOPE)

    # Expose local install directory to find_dependency
    list(APPEND CMAKE_MODULE_PATH "${DEPENDENCY_INSTALL}/cmake")
    set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE)
endfunction()

function(vendor_dependency DEPENDENCY_NAME)
    # Define path for the external project
    set(DEPENDENCY_INSTALL "${CMAKE_BINARY_DIR}/_external_projects/${DEPENDENCY_NAME}-install")
    
    # Vendor the dependency if it exists
    if(EXISTS "${DEPENDENCY_INSTALL}")
        message(STATUS "Installing vendored ${DEPENDENCY_NAME} to system...")
        install(
            DIRECTORY "${DEPENDENCY_INSTALL}/"
            DESTINATION "."
        )
    else()
        message(FATAL_ERROR "Vendored ${DEPENDENCY_NAME} not found.")
    endif()
endfunction()
