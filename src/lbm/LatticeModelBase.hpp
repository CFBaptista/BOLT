#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <type_traits>

/**
 * @class LatticeModelBase
 * @brief Class that specifies serves as base lattice models.
 *
 * This class serves as the base for lattice models used in lattice Boltzmann methods.
 * Derived classes must satisfy `LatticeModel` concept.
 */
class LatticeModelBase
{
};

/**
 * @concept LatticeModel
 * @brief Concept used for constraining template parameters to types of valid lattice models for
 * lattice Boltzmann methods.
 *
 * The `LatticeModel` concept specifies the required interface and type constraints for lattice
 * model types. A type that satisfies this concept must:
 * - Provide static member functions for dimension and size, returning a `std::size_t`.
 * - Constrain dimension is between 1 and 3 (inclusive) and size is at least 1.
 * - Provide static member functions for velocities and weights, returning appropriate `std::array`
 * types.
 * - Define a `value_type` that is a floating-point type.
 * - Inherit from `LatticeModelBase`.
 *
 * This concept is used to ensure that template parameters conform to the expected lattice model
 * interface.
 *
 * @tparam Derived Lattice model type to be checked.
 */
template <typename Derived>
concept LatticeModel = requires {
    requires std::floating_point<typename Derived::Real>;
    { Derived::dimension() } -> std::same_as<std::size_t>;
    requires(Derived::dimension() >= 1 && Derived::dimension() <= 3);
    { Derived::size() } -> std::same_as<std::size_t>;
    requires(Derived::size() >= 1);
    {
        Derived::velocities()
    } -> std::same_as<std::array<std::array<int, Derived::dimension()>, Derived::size()>>;
    { Derived::weights() } -> std::same_as<std::array<typename Derived::Real, Derived::size()>>;
    std::is_base_of_v<LatticeModelBase, Derived>;
};
