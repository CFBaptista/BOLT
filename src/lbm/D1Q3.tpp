#pragma once

#include "D1Q3.hpp"

template <std::floating_point Real>
constexpr auto D1Q3<Real>::dimension() noexcept -> std::size_t
{
    return dimension_;
}

template <std::floating_point Real>
constexpr auto D1Q3<Real>::size() noexcept -> std::size_t
{
    return size_;
}

template <std::floating_point Real>
constexpr auto D1Q3<Real>::velocities() noexcept
    -> std::array<std::array<int, D1Q3<Real>::dimension_>, D1Q3<Real>::size_>
{
    return velocities_;
}

template <std::floating_point Real>
constexpr auto D1Q3<Real>::weights() noexcept -> std::array<Real, D1Q3<Real>::size_>
{
    return weights_;
}
