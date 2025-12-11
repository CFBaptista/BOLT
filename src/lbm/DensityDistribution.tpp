#pragma once

#include <numeric>

#include "lbm/DensityDistribution.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Set>
DensityDistribution<Set>::DensityDistribution(const Vector<Real, Set::size()>& distribution
) noexcept
    : distribution_(distribution)
{
}

template <VelocitySet Set>
constexpr auto DensityDistribution<Set>::dimension() noexcept -> Count
{
    return Set::dimension();
}

template <VelocitySet Set>
constexpr auto DensityDistribution<Set>::size() noexcept -> Count
{
    return Set::size();
}

template <VelocitySet Set>
auto DensityDistribution<Set>::operator[](Count index) -> Real&
{
    return distribution_[index];
}

template <VelocitySet Set>
auto DensityDistribution<Set>::operator[](Count index) const -> const Real&
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
auto DensityDistribution<Set>::momentum() const noexcept -> Vector<Real, Set::dimension()>
{
    Vector<Real, Set::dimension()> macroscopicMomentum{};

    for (Count dir = 0; dir < Set::size(); ++dir)
    {
        const Real distributionValue{distribution_[dir]};

        for (Count dim = 0; dim < Set::dimension(); ++dim)
        {
            macroscopicMomentum[dim] += distributionValue * Set::velocities()[dir][dim];
        }
    }

    return macroscopicMomentum;
}

template <VelocitySet Set>
auto DensityDistribution<Set>::velocity(
    const Real& density,
    const Vector<Real, Set::dimension()>& momentum
) -> Vector<Real, Set::dimension()>
{
    Vector<Real, Set::dimension()> macroscopicVelocity{};

    for (Count dim = 0; dim < Set::dimension(); ++dim)
    {
        macroscopicVelocity[dim] = momentum[dim] / density;
    }

    return macroscopicVelocity;
}
