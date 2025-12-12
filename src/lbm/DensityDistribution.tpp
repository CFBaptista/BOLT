#pragma once

#include <numeric>

#include "lbm/DensityDistribution.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Set>
DensityDistribution<Set>::DensityDistribution(const Vector<Float, Set::size()>& distribution
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
auto DensityDistribution<Set>::operator[](Count index) -> Float&
{
    return distribution_[index];
}

template <VelocitySet Set>
auto DensityDistribution<Set>::operator[](Count index) const -> const Float&
{
    return distribution_[index];
}

template <VelocitySet Set>
auto DensityDistribution<Set>::density() const noexcept -> Float
{
    Float macroscopicDensity{std::accumulate(distribution_.begin(), distribution_.end(), Float{0})};
    return macroscopicDensity;
}

template <VelocitySet Set>
auto DensityDistribution<Set>::momentum() const noexcept -> Vector<Float, Set::dimension()>
{
    Vector<Float, Set::dimension()> macroscopicMomentum{};

    for (Count dir = 0; dir < Set::size(); ++dir)
    {
        const Float distributionValue{distribution_[dir]};

        for (Count dim = 0; dim < Set::dimension(); ++dim)
        {
            macroscopicMomentum[dim] += distributionValue * Set::velocities()[dir][dim];
        }
    }

    return macroscopicMomentum;
}

template <VelocitySet Set>
auto DensityDistribution<Set>::velocity(
    const Float& density,
    const Vector<Float, Set::dimension()>& momentum
) -> Vector<Float, Set::dimension()>
{
    Vector<Float, Set::dimension()> macroscopicVelocity{};

    for (Count dim = 0; dim < Set::dimension(); ++dim)
    {
        macroscopicVelocity[dim] = momentum[dim] / density;
    }

    return macroscopicVelocity;
}
