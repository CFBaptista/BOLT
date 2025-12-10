# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

### Added

- `VelocitySetBase`: CRTP base class for velocity sets.
- `VelocitySet`: Concept for constraining the template parameter of consumers of velocity sets.
- `D1Q3`: Class template for the D1Q3 velocity set.
- `D2Q9`: Class template for the D2Q9 velocity set.
- `D3Q27`: Class template for the D3Q27 velocity set.

- `NodeDistributionBase`: Base class for distributions at lattice nodes. 
- `NodeDistribution`: Concept for constraining the template parameter of consumers of node distributions.
- `DensityDistribution`: Class template for the distribution of density over a velocity set.

- `EquilibriumDistributionBase`: Base class for equilibrium distributions.
- `EquilibriumDistribution`: Concept for constraining the template parameter of consumers of equilibrium distributions.
- `DiscreteMaxwellBoltzmann`: Class template for the discrete Maxwell Boltzmann distribution approximated via a Hermite expansion. Currently only the second-order approximation is implemented.

- GitHub workflow for continuous integration (CI)
- Ubuntu 24.04 Dockerfile for installing dependencies needed CI workflow
- CMake target `Coverage` for running code coverage analysis

### Changed

-

### Deprecaed

-   

### Removed

-

### Fixed

-

### Security

-
