#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <type_traits>

/**
 * @class VelocitySetBase
 * @brief Class template that serves as CRTP base class for velocity sets.
 *
 * This class template serves as the CRTP base class for velocity sets. Derived classes must satisfy
 * the `VelocitySet` concept and consumers of Derived classes should contrain their template
 * parameter using the same concept.
 *
 * @tparam Derived The derived velocity set class.
 */
template <typename Derived>
class VelocitySetBase
{
public:
    VelocitySetBase() = delete;
    VelocitySetBase(const VelocitySetBase& other) = delete;
    VelocitySetBase(VelocitySetBase&& other) = delete;
    auto operator=(const VelocitySetBase<Derived>& other) -> VelocitySetBase& = delete;
    auto operator=(VelocitySetBase<Derived>&& other) -> VelocitySetBase& = delete;
    ~VelocitySetBase() = delete;

    /**
     * @brief Returns the spatial dimension of the derived velocity set.
     *
     * @return The spatial dimension.
     */
    static constexpr auto dimension() noexcept -> std::size_t;

    /**
     * @brief Returns the number of discrete velocity vectors of the derived velocity set.
     *
     * @return The number of discrete velocity vectors.
     */
    static constexpr auto size() noexcept -> std::size_t;

    /**
     * @brief Returns the discrete velocity vectors of the derived velocity set.
     *
     * @return The discrete velocity vectors in lattice units.
     */
    static constexpr auto velocities() noexcept -> decltype(auto);

    /**
     * @brief Returns the quadrature weight for each discrete velocity vector of the derived
     * velocity set.
     *
     * @return The weight for each discrete velocity vector.
     */
    static constexpr auto weights() noexcept -> decltype(auto);
};

/**
 * @concept VelocitySet
 * @brief Concept used for constraining the template parameter of consumers of velocity sets.
 *
 * The `VelocitySet` concept specifies the required interface and type constraints for velocity
 * set types. A type that satisfies this concept must:
 * - Provide static member functions for dimension and size, returning a `std::size_t`.
 * - Constrain dimension to be between 1 and 3 (inclusive) and size to be at least 1.
 * - Provide static member functions for velocities and weights, returning appropriate `std::array`
 * types.
 * - Define a `value_type` that is a floating-point type.
 * - Inherit from `VelocitySetBase<Derived>`.
 *
 * This concept is used to ensure that template parameters conform to the expected velocity set
 * interface.
 *
 * @tparam Derived Lattice model type to be checked.
 */
template <typename Derived>
concept VelocitySet = requires {
    requires std::floating_point<typename Derived::Real>;
    { Derived::dimension() } -> std::same_as<std::size_t>;
    requires(Derived::dimension() >= 1 && Derived::dimension() <= 3);
    { Derived::size() } -> std::same_as<std::size_t>;
    requires(Derived::size() >= 1);
    {
        Derived::velocities()
    } -> std::same_as<const std::array<std::array<int, Derived::dimension()>, Derived::size()>>;
    {
        Derived::weights()
    } -> std::same_as<const std::array<typename Derived::Real, Derived::size()>>;
    std::is_base_of_v<VelocitySetBase<Derived>, Derived>;
};

#include "VelocitySetBase.tpp"
