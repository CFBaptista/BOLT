#pragma once

#include <cstddef>

#include "LatticeModelBase.hpp"

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::dimension() noexcept -> std::size_t
{
    return Derived::dimension_;
}

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::size() noexcept -> std::size_t
{
    return Derived::size_;
}

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::velocities() noexcept -> decltype(auto)
{
    return Derived::velocities_;
}

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::weights() noexcept -> decltype(auto)
{
    return Derived::weights_;
}
