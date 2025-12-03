#pragma once

#include <cstddef>

#include "lbm/DensityDistribution.hpp"
#include "lbm/VelocitySetBase.hpp"

template <VelocitySet Set>
DensityDistribution<Set>::DensityDistribution(const std::array<Real, Set::size()>& distribution
) noexcept
    : distribution_(distribution)
{
}

template <VelocitySet Set>
constexpr auto DensityDistribution<Set>::dimension() -> std::size_t
{
    return Set::dimension();
}

template <VelocitySet Set>
constexpr auto DensityDistribution<Set>::size() -> std::size_t
{
    return Set::size();
}

template <VelocitySet Set>
auto DensityDistribution<Set>::operator[](std::size_t index) -> Real&
{
    return distribution_[index];
}

template <VelocitySet Set>
auto DensityDistribution<Set>::operator[](std::size_t index) const -> const Real&
{
    return distribution_[index];
}