#pragma once

#include <array>
#include <concepts>
#include <cstddef>

#include "VelocitySetBase.hpp"

/**
 * @class D1Q3
 * @brief Class template representing the D1Q3 velocity set.
 *
 * This class template contains the `static constexpr` data specific to the `D1Q3` velocity set.
 * Accessors are defined in the CRTP base class `VelocitySetBase`. Use the concept `VelocitySet`
 * to constrain the template parameter of consumers of this class.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = double>
class D1Q3 : public VelocitySetBase<D1Q3<T>>
{
public:
    using Real = T;

    friend class VelocitySetBase<D1Q3<T>>;

    D1Q3() = delete;
    D1Q3(const D1Q3& other) = delete;
    D1Q3(D1Q3&& other) = delete;
    auto operator=(const D1Q3& other) -> D1Q3& = delete;
    auto operator=(D1Q3&& other) -> D1Q3& = delete;
    ~D1Q3() = delete;

private:
    static constexpr std::size_t dimension_{1};

    static constexpr std::size_t size_{3};

    static constexpr std::array<std::array<T, dimension_>, size_> velocities_{
        {{{static_cast<T>(0)}}, {{static_cast<T>(1)}}, {{static_cast<T>(-1)}}}
    };

    static constexpr std::array<T, size_> weights_{
        static_cast<T>(4) / static_cast<T>(6), static_cast<T>(1) / static_cast<T>(6),
        static_cast<T>(1) / static_cast<T>(6)
    };
};
