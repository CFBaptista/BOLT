#pragma once

#include <array>
#include <concepts>
#include <cstddef>

#include "VelocitySetBase.hpp"

/**
 * @class D2Q9
 * @brief Class template representing the D2Q9 velocity set.
 *
 * @details This class template contains the `static constexpr` data specific to the `D1Q3` velocity
 * set. Accessors are defined in the CRTP base class `VelocitySetBase`. Use the concept
 * `VelocitySet` to constrain the template parameter of consumers of this class.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = double>
class D2Q9 : public VelocitySetBase<D2Q9<T>>
{
public:
    /// The floating-point type.
    using Real = T;

    /// Friend the CRTP base class to allow accessors in base to access private static data.
    friend class VelocitySetBase<D2Q9<T>>;

    D2Q9() = delete;
    D2Q9(const D2Q9& other) = delete;
    D2Q9(D2Q9&& other) = delete;
    auto operator=(const D2Q9& other) -> D2Q9& = delete;
    auto operator=(D2Q9&& other) -> D2Q9& = delete;
    ~D2Q9() = delete;

private:
    /// The spatial dimension.
    static constexpr std::size_t dimension_{2};

    /// The number of discrete velocity vectors.
    static constexpr std::size_t size_{9};

    /// The discrete velocity vectors in lattice units.
    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{
        {{{0, 0}},
         {{1, 0}},
         {{0, 1}},
         {{-1, 0}},
         {{0, -1}},
         {{1, 1}},
         {{-1, 1}},
         {{-1, -1}},
         {{1, -1}}}
    };

    /// The quadrature weights for each discrete velocity vector.
    static constexpr std::array<T, size_> weights_{
        static_cast<T>(4) / static_cast<T>(9),  static_cast<T>(1) / static_cast<T>(9),
        static_cast<T>(1) / static_cast<T>(9),  static_cast<T>(1) / static_cast<T>(9),
        static_cast<T>(1) / static_cast<T>(9),  static_cast<T>(1) / static_cast<T>(36),
        static_cast<T>(1) / static_cast<T>(36), static_cast<T>(1) / static_cast<T>(36),
        static_cast<T>(1) / static_cast<T>(36)
    };

    /// The multiplicative inverse of the speed of sound raised to the power of 2.
    static constexpr T soundSpeedInverseSquared_{static_cast<T>(3)};
};
