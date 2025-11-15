#pragma once

#include <array>
#include <concepts>

#include "LatticeModelBase.hpp"

/**
 * @class D3Q27
 * @brief Class template representing the D3Q27 lattice model.
 *
 * This class template contains the data specific to the D3Q27 lattice model.
 * Accessors are implemented in the CRTP base class LatticeModelBase.
 *
 * @tparam Real The floating-point type.
 */
template <std::floating_point Real>
class D3Q27 : public LatticeModelBase<D3Q27<Real>>
{
public:
    friend class LatticeModelBase<D3Q27<Real>>;

private:
    static inline constexpr std::size_t dimension_{3};
    static inline constexpr std::size_t size_{27};

    static inline constexpr std::array<std::array<int, dimension_>, size_> velocities_{
        {{{0, 0, 0}},   {{1, 0, 0}},   {{-1, 0, 0}},  {{0, 1, 0}},  {{0, -1, 0}},  {{0, 0, 1}},
         {{0, 0, -1}},  {{1, 1, 0}},   {{-1, 1, 0}},  {{1, -1, 0}}, {{-1, -1, 0}}, {{1, 0, 1}},
         {{-1, 0, 1}},  {{1, 0, -1}},  {{-1, 0, -1}}, {{0, 1, 1}},  {{0, -1, 1}},  {{0, 1, -1}},
         {{0, -1, -1}}, {{1, 1, 1}},   {{-1, 1, 1}},  {{1, -1, 1}}, {{-1, -1, 1}}, {{1, 1, -1}},
         {{-1, 1, -1}}, {{1, -1, -1}}, {{-1, -1, -1}}}
    };

    static inline constexpr std::array<Real, size_> weights_ = {
        static_cast<Real>(8) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216)
    };
};
