#pragma once

#include "D2Q9.hpp"

template <std::floating_point Real>
constexpr auto D2Q9<Real>::dimension() noexcept -> std::size_t
{
    return dimension_;
}

template <std::floating_point Real>
constexpr auto D2Q9<Real>::size() noexcept -> std::size_t
{
    return size_;
}

template <std::floating_point Real>
constexpr auto D2Q9<Real>::velocities() noexcept
    -> std::array<std::array<int, D2Q9<Real>::dimension_>, D2Q9<Real>::size_>
{
    return velocities_;
}

template <std::floating_point Real>
constexpr auto D2Q9<Real>::weights() noexcept -> std::array<Real, D2Q9<Real>::size_>
{
    return weights_;
}
