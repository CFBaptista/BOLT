#pragma once

#include "D3Q27.hpp"

template <std::floating_point Real>
constexpr auto D3Q27<Real>::dimension() noexcept -> std::size_t
{
    return dimension_;
}

template <std::floating_point Real>
constexpr auto D3Q27<Real>::size() noexcept -> std::size_t
{
    return size_;
}

template <std::floating_point Real>
constexpr auto D3Q27<Real>::velocities() noexcept
    -> std::array<std::array<int, D3Q27<Real>::dimension_>, D3Q27<Real>::size_>
{
    return velocities_;
}

template <std::floating_point Real>
constexpr auto D3Q27<Real>::weights() noexcept -> std::array<Real, D3Q27<Real>::size_>
{
    return weights_;
}
