#pragma once

#include <array>
#include <concepts>
#include <cstddef>

#include "LatticeModelBase.hpp"

/**
 * @class D2Q9
 * @brief Class template representing the D2Q9 lattice model.
 *
 * This class template contains the `static constexpr` data specific to the `D2Q9` lattice model.
 * Accessors are defined in the CRTP base class `LatticeModelBase`. Use the concept `LatticeModel`
 * to constrain the template parameter of consumers of this class.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = double>
class D2Q9 : public LatticeModelBase<D2Q9<T>>
{
public:
    using Real = T;

    friend class LatticeModelBase<D2Q9<T>>;

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