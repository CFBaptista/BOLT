#pragma once

#include <array>
#include <concepts>
#include <cstddef>

#include "VelocitySetBase.hpp"

/**
 * @class D3Q27
 * @brief Class template representing the D3Q27 velocity set.
 *
 * This class template contains the `static constexpr` data specific to the `D3Q27` velocity set.
 * Accessors are defined in the CRTP base class `VelocitySetBase`. Use the concept `VelocitySet`
 * to constrain the template parameter of consumers of this class.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = double>
class D3Q27 : public VelocitySetBase<D3Q27<T>>
{
public:
    /// The floating-point type.
    using Real = T;

    /// Friend the CRTP base class to allow accessors in base to access private static data.
    friend class VelocitySetBase<D3Q27<T>>;

    D3Q27() = delete;
    D3Q27(const D3Q27& other) = delete;
    D3Q27(D3Q27&& other) = delete;
    auto operator=(const D3Q27& other) -> D3Q27& = delete;
    auto operator=(D3Q27&& other) -> D3Q27& = delete;
    ~D3Q27() = delete;

private:
    /// The spatial dimension.
    static constexpr std::size_t dimension_{3};

    /// The number of discrete velocity vectors.
    static constexpr std::size_t size_{27};

    /// The discrete velocity vectors in lattice units.
    static constexpr std::array<std::array<T, dimension_>, size_> velocities_{
        {{{static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)}},
         {{static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)}},
         {{static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0)}},
         {{static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)}},
         {{static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0)}},
         {{static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)}},
         {{static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1)}},
         {{static_cast<T>(1), static_cast<T>(1), static_cast<T>(0)}},
         {{static_cast<T>(-1), static_cast<T>(1), static_cast<T>(0)}},
         {{static_cast<T>(1), static_cast<T>(-1), static_cast<T>(0)}},
         {{static_cast<T>(-1), static_cast<T>(-1), static_cast<T>(0)}},
         {{static_cast<T>(1), static_cast<T>(0), static_cast<T>(1)}},
         {{static_cast<T>(-1), static_cast<T>(0), static_cast<T>(1)}},
         {{static_cast<T>(1), static_cast<T>(0), static_cast<T>(-1)}},
         {{static_cast<T>(-1), static_cast<T>(0), static_cast<T>(-1)}},
         {{static_cast<T>(0), static_cast<T>(1), static_cast<T>(1)}},
         {{static_cast<T>(0), static_cast<T>(-1), static_cast<T>(1)}},
         {{static_cast<T>(0), static_cast<T>(1), static_cast<T>(-1)}},
         {{static_cast<T>(0), static_cast<T>(-1), static_cast<T>(-1)}},
         {{static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)}},
         {{static_cast<T>(-1), static_cast<T>(1), static_cast<T>(1)}},
         {{static_cast<T>(1), static_cast<T>(-1), static_cast<T>(1)}},
         {{static_cast<T>(-1), static_cast<T>(-1), static_cast<T>(1)}},
         {{static_cast<T>(1), static_cast<T>(1), static_cast<T>(-1)}},
         {{static_cast<T>(-1), static_cast<T>(1), static_cast<T>(-1)}},
         {{static_cast<T>(1), static_cast<T>(-1), static_cast<T>(-1)}},
         {{static_cast<T>(-1), static_cast<T>(-1), static_cast<T>(-1)}}}
    };

    /// The quadrature weights for each discrete velocity vector.
    static constexpr std::array<T, size_> weights_{
        static_cast<T>(8) / static_cast<T>(27),  static_cast<T>(2) / static_cast<T>(27),
        static_cast<T>(2) / static_cast<T>(27),  static_cast<T>(2) / static_cast<T>(27),
        static_cast<T>(2) / static_cast<T>(27),  static_cast<T>(2) / static_cast<T>(27),
        static_cast<T>(2) / static_cast<T>(27),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(216),
        static_cast<T>(1) / static_cast<T>(216), static_cast<T>(1) / static_cast<T>(216),
        static_cast<T>(1) / static_cast<T>(216), static_cast<T>(1) / static_cast<T>(216),
        static_cast<T>(1) / static_cast<T>(216), static_cast<T>(1) / static_cast<T>(216),
        static_cast<T>(1) / static_cast<T>(216)
    };

    /// The multiplicative inverse of the speed of sound raised to the power of 2.
    static constexpr T soundSpeedInverseSquared_{static_cast<T>(3)};
};
