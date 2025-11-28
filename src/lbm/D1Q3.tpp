#pragma once

#include "D1Q3.hpp"

template <std::floating_point Real>
constexpr auto D1Q3<Real>::dimension() -> std::size_t
{
    return dimension_;
}

template <std::floating_point Real>
constexpr auto D1Q3<Real>::size() -> std::size_t
{
    return size_;
}

template <std::floating_point Real>
constexpr auto
D1Q3<Real>::velocities() -> std::array<std::array<int, D1Q3<Real>::dimension_>, D1Q3<Real>::size_>
{
    return velocities_;
}

template <std::floating_point Real>
constexpr auto D1Q3<Real>::weights() -> std::array<Real, D1Q3<Real>::size_>
{
    return weights_;
}
