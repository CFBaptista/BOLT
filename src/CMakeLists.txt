# Copy compile_commands.json from the preset build directory to root build directory
add_custom_target(CompileCommands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_BINARY_DIR}/../compile_commands.json"
    COMMENT "Copying compile_commands.json to root build directory"
    VERBATIM
)

# Define compile flags based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(COMPILE_FLAGS -g -O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(COMPILE_FLAGS -O3)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(COMPILE_FLAGS -g -O2)
endif()

# Define coverage flags based on compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COVERAGE_FLAGS -fprofile-instr-generate -fcoverage-mapping -fno-inline -fno-elide-constructors -Wno-unused-template)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COVERAGE_FLAGS --coverage fno-inline -fno-inline-functions -fno-inline-small-functions)
endif()

# Custom target for coverage report using LLVM toolchain
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    find_program(PYTHON_EXECUTABLE_PATH python3)
    find_program(LLVM_PROFDATA_PATH llvm-profdata)
    find_program(LLVM_COV_PATH llvm-cov)
    
    if(PYTHON_EXECUTABLE_PATH AND LLVM_PROFDATA_PATH AND LLVM_COV_PATH)
        add_custom_target(Coverage
            COMMAND ${PYTHON_EXECUTABLE_PATH} ${CMAKE_SOURCE_DIR}/script/collect_extension_files.py ${CMAKE_BINARY_DIR}/coverage/llvm profraw
            COMMAND ${LLVM_PROFDATA_PATH} merge -sparse @${CMAKE_BINARY_DIR}/coverage/llvm/profraw_files.dat -o ${CMAKE_BINARY_DIR}/coverage/llvm/coverage.profdata
            COMMAND ${LLVM_COV_PATH} show ${CMAKE_BINARY_DIR}/test/lbm/lbm_test -instr-profile=${CMAKE_BINARY_DIR}/coverage/llvm/coverage.profdata -format=html -output-dir=${CMAKE_BINARY_DIR}/coverage -ignore-filename-regex=${CMAKE_SOURCE_DIR}/test
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running coverage analysis"
            VERBATIM
        )
    else()
        message(WARNING
            "Coverage target is not created due to missing dependencies:\n"
            "    - llvm-cov: ${LLVM_COV_PATH}\n"
            "    - llvm-profdata: ${LLVM_PROFDATA_PATH}\n"
            "    - python3: ${PYTHON_EXECUTABLE_PATH}"
        )
    endif()

endif()

# Custom target for coverage report using GNU toolchain
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)

    if(LCOV_PATH AND GENHTML_PATH)
        add_custom_target(Coverage
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
            COMMAND ${LCOV_PATH} --capture --directory ${CMAKE_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info
            COMMAND ${GENHTML_PATH} ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running coverage analysis"
            VERBATIM
        )
    else()
        message(WARNING
            "Coverage target is not created due to missing dependencies.\n"
            "    - genhtml: ${GENHTML_PATH}\n"
            "    - lcov: ${LCOV_PATH}"
        )
    endif()

endif()

add_subdirectory(lbm)
