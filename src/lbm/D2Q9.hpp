#pragma once

#include <array>
#include <concepts>
#include <cstddef>

#include "VelocitySetBase.hpp"

/**
 * @class D2Q9
 * @brief Class template representing the D2Q9 velocity set.
 *
 * This class template contains the `static constexpr` data specific to the `D2Q9` velocity set.
 * Accessors are defined in the CRTP base class `VelocitySetBase`. Use the concept `VelocitySet`
 * to constrain the template parameter of consumers of this class.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = double>
class D2Q9 : public VelocitySetBase<D2Q9<T>>
{
public:
    using Real = T;

    friend class VelocitySetBase<D2Q9<T>>;

    D2Q9() = delete;
    D2Q9(const D2Q9& other) = delete;
    D2Q9(D2Q9&& other) = delete;
    auto operator=(const D2Q9& other) -> D2Q9& = delete;
    auto operator=(D2Q9&& other) -> D2Q9& = delete;
    ~D2Q9() = delete;

private:
    static constexpr std::size_t dimension_{2};

    static constexpr std::size_t size_{9};

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

    static constexpr std::array<T, size_> weights_{
        static_cast<T>(4) / static_cast<T>(9),  static_cast<T>(1) / static_cast<T>(9),
        static_cast<T>(1) / static_cast<T>(9),  static_cast<T>(1) / static_cast<T>(9),
        static_cast<T>(1) / static_cast<T>(9),  static_cast<T>(1) / static_cast<T>(36),
        static_cast<T>(1) / static_cast<T>(36), static_cast<T>(1) / static_cast<T>(36),
        static_cast<T>(1) / static_cast<T>(36)
    };
};