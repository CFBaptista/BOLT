#pragma once

#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <typename Derived>
constexpr auto VelocitySetBase<Derived>::dimension() noexcept -> Count
{
    return Derived::dimension_;
}

template <typename Derived>
constexpr auto VelocitySetBase<Derived>::size() noexcept -> Count
{
    return Derived::size_;
}

template <typename Derived>
constexpr auto VelocitySetBase<Derived>::velocities() noexcept -> decltype(auto)
{
    return Derived::velocities_;
}

template <typename Derived>
constexpr auto VelocitySetBase<Derived>::weights() noexcept -> decltype(auto)
{
    return Derived::weights_;
}

template <typename Derived>
constexpr auto VelocitySetBase<Derived>::soundSpeedInverseSquared() noexcept -> decltype(auto)
{
    return Derived::soundSpeedInverseSquared_;
}
