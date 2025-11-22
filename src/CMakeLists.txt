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
    set(COVERAGE_FLAGS -fprofile-instr-generate -fcoverage-mapping)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COVERAGE_FLAGS --coverage)
endif()

# Custom target for coverage report (only for LLVM)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    find_program(LLVM_PROFDATA_PATH llvm-profdata)
    find_program(LLVM_COV_PATH llvm-cov)
    if(LLVM_PROFDATA_PATH AND LLVM_COV_PATH)
        add_custom_target(Coverage
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
            COMMAND ${LLVM_PROFDATA_PATH} merge -sparse ${CMAKE_BINARY_DIR}/test/lbm/default.profraw -o ${CMAKE_BINARY_DIR}/coverage.profdata
            COMMAND ${LLVM_COV_PATH} show ./test/lbm/lbm_test -instr-profile=${CMAKE_BINARY_DIR}/coverage.profdata -format=html -output-dir=${CMAKE_BINARY_DIR}/coverage
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running coverage analysis with llvm-cov and llvm-profdata"
            VERBATIM
        )
    else()
        message(WARNING "llvm-profdata or llvm-cov not found. Coverage target will not be available.")
    endif()
endif()

# Custom target for coverage report (only for GNU)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)
    if(LCOV_PATH AND GENHTML_PATH)
        add_custom_target(Coverage
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
            COMMAND ${LCOV_PATH} --capture --directory ../../ --output-file ${CMAKE_BINARY_DIR}/coverage.info
            COMMAND ${GENHTML_PATH} ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running coverage analysis with LCOV and genhtml"
            VERBATIM
        )
    else()
        message(WARNING "LCOV or genhtml not found. Coverage target will not be available.")
    endif()
endif()

add_subdirectory(lbm)
