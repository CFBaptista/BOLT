#pragma once

#include <array>
#include <concepts>

#include "LatticeModelBase.hpp"

constexpr std::size_t D1Q3Dimension = 1;
constexpr std::size_t D1Q3Size = 3;

/**
 * @class D1Q3
 * @brief Class template representing the D1Q3 lattice model.
 *
 * This class template contains the data specific to the D1Q3 lattice model.
 * Accessors are implemented in the CRTP base class LatticeModelBase.
 *
 * @tparam Real The floating-point type.
 */
template <std::floating_point Real>
class D1Q3 : public LatticeModelBase<D1Q3<Real>, Real, D1Q3Dimension, D1Q3Size>
{
public:
    friend class LatticeModelBase<D1Q3<Real>, Real, D1Q3Dimension, D1Q3Size>;

private:
    static constexpr std::array<std::array<int, D1Q3Dimension>, D1Q3Size> velocities_{
        {{{0}}, {{1}}, {{-1}}}
    };

    static constexpr std::array<Real, D1Q3Size> weights_{
        static_cast<Real>(4) / static_cast<Real>(6), static_cast<Real>(1) / static_cast<Real>(6),
        static_cast<Real>(1) / static_cast<Real>(6)
    };
};
