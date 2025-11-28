#pragma once

#include "D3Q27.hpp"

template <std::floating_point Real>
constexpr auto D3Q27<Real>::dimension() -> std::size_t
{
    return dimension_;
}

template <std::floating_point Real>
constexpr auto D3Q27<Real>::size() -> std::size_t
{
    return size_;
}

template <std::floating_point Real>
constexpr auto
D3Q27<Real>::velocities() -> std::array<std::array<int, D3Q27<Real>::dimension_>, D3Q27<Real>::size_>
{
    return velocities_;
}

template <std::floating_point Real>
constexpr auto D3Q27<Real>::weights() -> std::array<Real, D3Q27<Real>::size_>
{
    return weights_;
}
