#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <type_traits>

/**
 * @class VelocitySetBase
 *
 * @brief CRTP base class for velocity sets.
 *
 * @details This class template serves as the CRTP base class for velocity sets. Derived classes
 * should satisfy the `VelocitySet` concept. Consumers of Derived classes can use that concept to
 * enforce compliance in their template parameter(s).
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
     * @fn dimension
     *
     * @brief Returns the spatial dimension of the velocity set.
     *
     * @return The spatial dimension.
     */
    static constexpr auto dimension() noexcept -> std::size_t;

    /**
     * @fn size
     *
     * @brief Returns the number of discrete velocity vectors of the velocity set.
     *
     * @return The number of discrete velocity vectors.
     */
    static constexpr auto size() noexcept -> std::size_t;

    /**
     * @fn velocities
     *
     * @brief Returns the discrete velocity vectors of the velocity set.
     *
     * @return The discrete velocity vectors in lattice units.
     */
    static constexpr auto velocities() noexcept -> decltype(auto);

    /**
     * @fn weights
     *
     * @brief Returns the quadrature weight for each discrete velocity vector of the derived
     * velocity set.
     *
     * @return The weight for each discrete velocity vector.
     */
    static constexpr auto weights() noexcept -> decltype(auto);
};

/**
 * @concept VelocitySet
 *
 * @brief Concept used for constraining the template parameter of consumers of velocity sets.
 *
 * @details The `VelocitySet` concept specifies the required interface and type constraints for
 * velocity set types. A type that satisfies this concept:
 * - Provides static member functions for dimension and size, both returning a `std::size_t`.
 * - Has a dimension between 1 and 3 (inclusive) and a size of at least 1.
 * - Provides static member functions for velocity vectors and weights, both returning appropriate
 * `std::array` types.
 * - Defines a value type named Real that is a floating-point type.
 * - Inherits from `VelocitySetBase<Derived>`.
 *
 * @tparam Derived Velocity set type to be checked.
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
    } -> std::same_as<const std::array<
          std::array<typename Derived::Real, Derived::dimension()>, Derived::size()>>;
    {
        Derived::weights()
    } -> std::same_as<const std::array<typename Derived::Real, Derived::size()>>;
    std::is_base_of_v<VelocitySetBase<Derived>, Derived>;
};

#include "VelocitySetBase.tpp"
