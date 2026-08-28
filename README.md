# BOLT

*BOLT (Boltzmann Operator Lattice Toolkit) is a C++ library for Computational Fluid Dynamics based on the Lattice Boltzmann Method.*

[![Dev](https://img.shields.io/badge/docs-dev-blue.svg)](https://CFBaptista.github.io/BOLT/)
[![Build Status](https://github.com/CFBaptista/BOLT/actions/workflows/CI.yml/badge.svg?branch=master)](https://github.com/CFBaptista/BOLT/actions/workflows/CI.yml?query=branch%3Amaster)
[![codecov](https://codecov.io/gh/CFBaptista/BOLT/graph/badge.svg?token=MMSVONVDIG)](https://codecov.io/gh/CFBaptista/BOLT)
[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue?logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/)
[![CMake](https://img.shields.io/badge/CMake-3.30%2B-064F8C?logo=cmake&logoColor=white)](https://github.com/CFBaptista/BOLT/blob/master/CMakeLists.txt)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/CFBaptista/BOLT/blob/master/LICENSE.md)

## Getting Started

### Prerequisites

| # | Category | Dependency | Requirement | Provisioning |
| - | -------- | ---- | ----------- | ------ |
| 1 | Build system generator | [CMake](https://github.com/kitware/cmake) 3.30+ | Required | System |
| 2 | Build system | [Ninja](https://github.com/ninja-build/ninja) 1.13.2+ | Required | System |
| 3 | C++23 compiler | [Clang](https://github.com/llvm/llvm-project) 21+ / [GCC](https://github.com/gcc-mirror/gcc) 14+| Required | System |
| 4 | CLI parser | [CLI11](https://github.com/cliutils/cli11) 2.6.2+ | Required | System / vendored |
| 5 | TOML parser | [toml++](https://github.com/marzer/tomlplusplus) 3.4.0+ | Required | System / vendored |
| 6 | Logging framework | [Quill](https://github.com/odygrd/quill) 11.1.0+ | Required | System / vendored |
| 7 | Testing framework | [Catch2](https://github.com/catchorg/Catch2) 3.15.1+ | Optional | System / vendored |
| 8 | Documentation framework | [doxygen](https://github.com/doxygen/doxygen) 1.15.0+ | Optional | System |

### Quick Build

Clone, configure and build using the `default` preset:

```bash
git clone https://github.com/CFBaptista/BOLT.git
cd BOLT
cmake --preset default
cmake --build --preset default
```

### Run Tests

To run tests, configure with `-DBUILD_TESTING=ON` (requires **Catch2**):

```bash
cmake --preset default -DBUILD_TESTING=ON
cmake --build --preset default
ctest --preset default
```

### Build Documentation

To build documentation, configure with `-DBUILD_DOCS=ON` (requires **doxygen**):

```bash
cmake --preset default -DBUILD_DOCS=ON
cmake --build --preset default --target docs
```

Documentation in HTML is then located at: `build/default/doc/html/index.html`

### Install

Install `BOLT` to a specified prefix (e.g. `/usr/local`):

```bash
cmake --install build/default --prefix /usr/local
```
To use the installed `BOLT` in your project add this to your CMake build system:

```cmake
find_package(BOLT REQUIRED)
target_link_libraries(your_target PRIVATE bolt::lbm)
```

# Contact

Carlos Fernando Baptista (cfd.baptista@gmail.com)
