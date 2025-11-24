#pragma once

#include <array>
#include <concepts>

#include "LatticeModelBase.hpp"

constexpr std::size_t D3Q27Dimension = 3;
constexpr std::size_t D3Q27Size = 27;

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
class D3Q27 : public LatticeModelBase<D3Q27<Real>, Real, D3Q27Dimension, D3Q27Size>
{
public:
    friend class LatticeModelBase<D3Q27<Real>, Real, D3Q27Dimension, D3Q27Size>;

private:
    static constexpr std::array<std::array<int, D3Q27Dimension>, D3Q27Size> velocities_{
        {{{0, 0, 0}},   {{1, 0, 0}},   {{-1, 0, 0}},  {{0, 1, 0}},  {{0, -1, 0}},  {{0, 0, 1}},
         {{0, 0, -1}},  {{1, 1, 0}},   {{-1, 1, 0}},  {{1, -1, 0}}, {{-1, -1, 0}}, {{1, 0, 1}},
         {{-1, 0, 1}},  {{1, 0, -1}},  {{-1, 0, -1}}, {{0, 1, 1}},  {{0, -1, 1}},  {{0, 1, -1}},
         {{0, -1, -1}}, {{1, 1, 1}},   {{-1, 1, 1}},  {{1, -1, 1}}, {{-1, -1, 1}}, {{1, 1, -1}},
         {{-1, 1, -1}}, {{1, -1, -1}}, {{-1, -1, -1}}}
    };

    static constexpr std::array<Real, D3Q27Size> weights_{
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
