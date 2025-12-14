#pragma once

#include <numeric>

#include "lbm/DensityDistribution.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Velocity>
DensityDistribution<Velocity>::DensityDistribution(
    const Vector<Float, Velocity::size()>& distribution
) noexcept
    : distribution_(distribution)
{
}

template <VelocitySet Velocity>
constexpr auto DensityDistribution<Velocity>::dimension() noexcept -> Count
{
    return Velocity::dimension();
}

template <VelocitySet Velocity>
constexpr auto DensityDistribution<Velocity>::size() noexcept -> Count
{
    return Velocity::size();
}

template <VelocitySet Velocity>
auto DensityDistribution<Velocity>::operator[](Count index) -> Float&
{
    return distribution_[index];
}

template <VelocitySet Velocity>
auto DensityDistribution<Velocity>::operator[](Count index) const -> const Float&
{
    return distribution_[index];
}

template <VelocitySet Velocity>
auto DensityDistribution<Velocity>::density() const noexcept -> Float
{
    Float macroscopicDensity{std::accumulate(distribution_.begin(), distribution_.end(), Float{0})};
    return macroscopicDensity;
}

template <VelocitySet Velocity>
auto DensityDistribution<Velocity>::momentum() const noexcept
    -> Vector<Float, Velocity::dimension()>
{
    Vector<Float, Velocity::dimension()> macroscopicMomentum{};

    for (Count dir = 0; dir < Velocity::size(); ++dir)
    {
        const Float distributionValue{distribution_[dir]};

        for (Count dim = 0; dim < Velocity::dimension(); ++dim)
        {
            macroscopicMomentum[dim] += distributionValue * Velocity::velocities()[dir][dim];
        }
    }

    return macroscopicMomentum;
}

template <VelocitySet Velocity>
auto DensityDistribution<Velocity>::velocity(
    const Float& density,
    const Vector<Float, Velocity::dimension()>& momentum
) -> Vector<Float, Velocity::dimension()>
{
    Vector<Float, Velocity::dimension()> macroscopicVelocity{};

    for (Count dim = 0; dim < Velocity::dimension(); ++dim)
    {
        macroscopicVelocity[dim] = momentum[dim] / density;
    }

    return macroscopicVelocity;
}
