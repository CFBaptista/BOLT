# ==================================================================================================
# Project   : BOLT (Boltzmann Operator Lattice Toolkit)
# License   : MIT
# Author    : Carlos Fernando Baptista
# Contact   : cfd.baptista@gmail.com
# ==================================================================================================

cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    BOLT
    VERSION 0.1.0
    DESCRIPTION "BOLT (Boltzmann Operator Lattice Toolkit) is a C++ library for Computational Fluid Dynamics based on the Lattice Boltzmann Method."
    HOMEPAGE_URL "https://github.com/CFBaptista/BOLT"
    LANGUAGES CXX
)

include(cmake/initialization.cmake)

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(test)
add_subdirectory(doc)
