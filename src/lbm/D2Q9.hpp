#pragma once

#include <array>
#include <concepts>

#include "LatticeModelBase.hpp"

constexpr std::size_t D2Q9Dimension = 2;
constexpr std::size_t D2Q9Size = 9;

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
class D2Q9 : public LatticeModelBase<D2Q9<Real>, Real, D2Q9Dimension, D2Q9Size>
{
public:
    friend class LatticeModelBase<D2Q9<Real>, Real, D2Q9Dimension, D2Q9Size>;

private:
    static constexpr std::array<std::array<int, D2Q9Dimension>, D2Q9Size> velocities_{
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

    static constexpr std::array<Real, D2Q9Size> weights_{
        static_cast<Real>(4) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36), static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36)
    };
};
