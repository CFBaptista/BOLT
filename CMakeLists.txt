# Set minimum CMake version
cmake_minimum_required(VERSION 3.30.5)

# Set project information
project(
    BOLT
    VERSION 0.1.0
    DESCRIPTION "C++ library for Computational Fluid Dynamics based on the Lattice Boltzmann Method"
    LANGUAGES CXX
)

# Set strict ISO C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable export of compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add a build target that copies compile_commands.json from the preset build directory to the root
# build directory
if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_target(export_compile_commands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/compile_commands.json"
            "${CMAKE_BINARY_DIR}/../compile_commands.json"
        COMMENT "Copying compile_commands.json to the parent directory of ${CMAKE_BINARY_DIR}"
        VERBATIM
    )
endif()

# Add test root directory
set(TESTABLE_BUILD_TYPES 
    Debug
    RelWithDebInfo
)
if (CMAKE_BUILD_TYPE IN_LIST TESTABLE_BUILD_TYPES)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

# Add documentation root directory
add_subdirectory(doc)
