#pragma once

#include <cstddef>
#include <numeric>

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

template <VelocitySet Set>
auto DensityDistribution<Set>::density() const noexcept -> Real
{
    Real macroscopicDensity{std::accumulate(distribution_.begin(), distribution_.end(), Real{0})};
    return macroscopicDensity;
}

template <VelocitySet Set>
auto DensityDistribution<Set>::momentum() const noexcept -> std::array<Real, Set::dimension()>
{
    std::array<Real, Set::dimension()> macroscopicMomentum{};

    for (std::size_t dir = 0; dir < Set::size(); ++dir)
    {
        const Real distributionValue{distribution_[dir]};

        for (std::size_t dim = 0; dim < Set::dimension(); ++dim)
        {
            macroscopicMomentum[dim] += distributionValue * Set::velocities()[dir][dim];
        }
    }

    return macroscopicMomentum;
}

template <VelocitySet Set>
auto DensityDistribution<Set>::velocity(
    const Real& density,
    const std::array<Real, Set::dimension()>& momentum
) const -> std::array<Real, Set::dimension()>
{
    std::array<Real, Set::dimension()> macroscopicVelocity{};

    for (std::size_t dim = 0; dim < Set::dimension(); ++dim)
    {
        macroscopicVelocity[dim] = momentum[dim] / density;
    }

    return macroscopicVelocity;
}
