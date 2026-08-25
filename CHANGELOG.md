# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

### Added

**API**
- `bolt::aligned_allocator`: Custom aligned memory allocator.
- `bolt::array`: Multi-dimensional container.
- `bolt::lbm::LatticeModel`: Concept for validating lattice model requirements.
- `bolt::lbm::D1Q3`, `bolt::lbm::D2Q9`, and `bolt::lbm::D3Q27`: Lattice model specifiers.
- `bolt::lbm::DistributionField`: Class template for storing lattice distributions on 1D, 2D, and 3D Cartesian grids.
- `bolt::core::create_logger`: Create a `quill`-based logger that logs to the console and a file on disk.
- `bolt::config::ConfigurationManager`: Class for managing the parsing and validation of command-line arguments and configurations read from an input TOML file.
- `bolt::config::IOConfiguration`: Class holding validated I/O configurations.
- `bolt::config::TimeConfiguration`: Class holding simulation time configurations.
- `bolt::config::SimulationTime`: Simulation time object managing discrete time in a solver.

**Applications and libraries**

| # | Name | Type | Description |
|---|------|------|-------------|
| 1 | `bolt` | Executable | Command-line application for simulating fluid dynamics cases using the Lattice Boltzmann Method. The application depends on `quill` as the logging framework. |
| 2 | `bolt::compile_settings` | Interface library | Empty library used only for propagating compilation settings. `BOLT` libraries inherit settings by linking against this library. |
| 3 | `bolt::config` | Static library | Configuration types and configuration manager for parsing and validating inputs to an application from the command line and a configuration file. |
| 4 | `bolt::core` | Static library | Fundamental utilities needed by other libraries (e.g. generic algorithms, containers, concepts, etc.). |
| 5 | `bolt::lbm` | Interface library | LBM models and numerical algorithms. |
| 6 | `copy_compile_commands` | Utility | Utility for copying the `compile_commands.json` file from a preset's build directory to the root build directory. |
| 7 | `docs` | Utility | Utility for building documentation.  |

**Dependencies**

| # | Name | Minimal version | Dependency Type | Source | Purpose |
|---|------|-----------------|------| ------ | ------- |
| 1 | [Catch2](https://github.com/catchorg/Catch2) | 3.5.11 | Private build-time dependency (optional)  | System or vendored  | Testing framework |
| 2 | [CLI11](https://github.com/cliutils/cli11) | 2.6.2 | Private build-time dependency | System or vendored | Parse command-line arguments |
| 3 | [Doxygen](https://github.com/doxygen/doxygen) | 1.15.0 | Private build-time dependency (optional) | System | Documentation framework |
| 4 | [Quill](https://github.com/odygrd/quill) | 11.1.0 | Public interface dependency | System or vendored | Logging framework |
| 5 | [TOML](https://github.com/toml-lang/toml) | 3.4.0 | Private build-time dependency | System or vendored | Read TOML file as configuration for the `bolt` application |

**Build system**
- CMake C++23 project named `BOLT` with initial version `0.1.0`.
- CMake presets supporting `GNU` and `LLVM` toolchains and `Debug`, `Release` and `RelWithDebInfo` builds.
- CMake functions for managing third-party dependencies supporting both system and vendored versions.
- Export of `BOLT` as CMake package, consumers can find it using `find_package(BOLT)`.
- If `quill` is not found on the system or the user explicitly choses for the vendored version then `quill` is exported alongside `BOLT`.

**CI/CD**
- Development container specification and Dockerfile for a reproducible development environment (also used on GitHub Actions).
- GitHub Actions workflows for continuous integration and documentation deployment.
- Tooling configuration for `clang-format`, `clang-tidy`, `clangd`, and `cppcheck`.
- Doxygen-based public API documentation and BibTex-based bibliography support.

### Changed

- None.

### Deprecated

- None.

### Removed

- None.

### Fixed

- None

### Security

- None.
