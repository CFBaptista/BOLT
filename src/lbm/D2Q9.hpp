#pragma once

#include <array>
#include <concepts>

#include "LatticeModelBase.hpp"

/**
 * @class D2Q9
 * @brief Class template representing the D2Q9 lattice model.
 *
 * This class template contains the data specific to the D2Q9 lattice model.
 * Accessors are implemented in the CRTP base class LatticeModelBase.
 *
 * @tparam Real The floating-point type.
 */
template <std::floating_point Real>
class D2Q9 : public LatticeModelBase<D2Q9<Real>>
{
public:
    friend class LatticeModelBase<D2Q9<Real>>;

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

    static constexpr std::array<Real, size_> weights_{
        static_cast<Real>(4) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36), static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36)
    };
};
