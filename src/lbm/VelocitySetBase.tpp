#pragma once

#include <cstddef>

#include "VelocitySetBase.hpp"

template <typename Derived>
constexpr auto VelocitySetBase<Derived>::dimension() noexcept -> std::size_t
{
    return Derived::dimension_;
}

template <typename Derived>
constexpr auto VelocitySetBase<Derived>::size() noexcept -> std::size_t
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

template <typename Derived>
constexpr auto VelocitySetBase<Derived>::soundSpeedInverseTessarected() noexcept -> decltype(auto)
{
    return Derived::soundSpeedInverseTessarected_;
}
