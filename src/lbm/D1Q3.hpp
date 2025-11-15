#pragma once

#include <array>
#include <concepts>

#include "LatticeModelBase.hpp"

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
class D1Q3 : public LatticeModelBase<D1Q3<Real>>
{
public:
    friend class LatticeModelBase<D1Q3<Real>>;

private:
    static inline constexpr std::size_t dimension_{1};
    static inline constexpr std::size_t size_{3};

    static inline constexpr std::array<std::array<int, dimension_>, size_> velocities_{
        {{{0}}, {{1}}, {{-1}}}
    };

    static inline constexpr std::array<Real, size_> weights_ = {
        static_cast<Real>(4) / static_cast<Real>(6), static_cast<Real>(1) / static_cast<Real>(6),
        static_cast<Real>(1) / static_cast<Real>(6)
    };
};
