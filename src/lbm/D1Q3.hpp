#pragma once
// #include <cmath>
#include <concepts>

#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

/**
 * @class D1Q3
 *
 * @brief Class template representing the D1Q3 velocity set.
 *
 * @details This class template contains the `static constexpr` data specific to the `D1Q3` velocity
 * set. Accessors are defined in the CRTP base class `VelocitySetBase`. Use the concept
 * `VelocitySet` to constrain the template parameter of consumers of this class.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = Real>
class D1Q3 : public VelocitySetBase<D1Q3<T>>
{
public:
    /// The floating-point type.
    using Float = T;

    /// Friend the CRTP base class to allow accessors in base to access private static data.
    friend class VelocitySetBase<D1Q3<T>>;

    D1Q3() = delete;
    D1Q3(const D1Q3& other) = delete;
    D1Q3(D1Q3&& other) = delete;
    auto operator=(const D1Q3& other) -> D1Q3& = delete;
    auto operator=(D1Q3&& other) -> D1Q3& = delete;
    ~D1Q3() = delete;

private:
    /// The spatial dimension.
    static constexpr Count dimension_{1};

    /// The number of discrete velocity vectors.
    static constexpr Count size_{3};

    /// The discrete velocity vectors in lattice units.
    static constexpr Matrix<Index, size_, dimension_> velocities_{{{{0}}, {{1}}, {{-1}}}};

    /// The quadrature weights for each discrete velocity vector.
    static constexpr Vector<T, size_> weights_{
        static_cast<T>(4) / static_cast<T>(6), static_cast<T>(1) / static_cast<T>(6),
        static_cast<T>(1) / static_cast<T>(6)
    };

    /// The multiplicative inverse of the speed of sound raised to the power of 2.
    static constexpr T soundSpeedInverseSquared_{static_cast<T>(3)};
};
