# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

### Added

- Initial CMake-based project structure for the BOLT library, including source, test, and documentation targets.
- CMake presets for GNU and LLVM debug, release and relWithDebInfo configurations.
- Development container configuration and Docker image definition for a reproducible development environment (also used by GitHub Action workflows).
- GitHub Actions workflows for continuous integration and documentation deployment.
- Doxygen-based documentation build configuration and BibTex-based bibliography support.
- Repository-wide tooling configuration for `clang-format`, `clang-tidy`, `clangd`, and `cppcheck`.

- Aligned storage utilities with `AlignedAllocator` custom allocator and multi-dimensional `AlignedArray` container.
- `LatticeModel` concept for validating lattice model requirements.
- Lattice model interfaces for `D1Q3`, `D2Q9`, and `D3Q27`.
- `DistributionField` template for storing lattice distributions on 1D, 2D, and 3D Cartesian grids.
- `SimulationTime` template for managing fixed-step simulation time in the core module.

### Changed

- None.

### Deprecated

- None.

### Removed

- None.

### Fixed

- Added direct `<concepts>` includes to lattice model headers to satisfy include-cleaner diagnostics.

### Security

- None.
