# Check if test framework is installed
find_package(Catch2 3 REQUIRED)
include(Catch)

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

# Add test directories
add_subdirectory(lbm)
