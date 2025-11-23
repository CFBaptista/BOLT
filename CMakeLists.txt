# Set minimum CMake version
cmake_minimum_required(VERSION 3.28.3)

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

# Enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source root directory
add_subdirectory(src)

# Add test root directory
include(CTest)
add_subdirectory(test)

# Add documentation root directory
add_subdirectory(doc)
