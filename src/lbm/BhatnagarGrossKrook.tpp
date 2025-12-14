#pragma once

#include <stdexcept>

#include "lbm/BhatnagarGrossKrook.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Velocity, EquilibriumDistribution Equilibrium>
BhatnagarGrossKrook<Velocity, Equilibrium>::BhatnagarGrossKrook(
    const Float& timeStep,
    const Float& relaxationTime
)
    : timeStep_(timeStep), relaxationTime_(relaxationTime),
      relaxationFactor_(timeStep / relaxationTime),
      oneMinusRelaxationFactor_(static_cast<Float>(1) - relaxationFactor_)
{
    if (timeStep_ <= 0)
    {
        throw std::invalid_argument("Time step must be positive.");
    }

    if (relaxationTime_ <= 0)
    {
        throw std::invalid_argument("Relaxation time must be positive.");
    }
}

template <VelocitySet Velocity, EquilibriumDistribution Equilibrium>
auto BhatnagarGrossKrook<Velocity, Equilibrium>::collide(
    const DensityDistribution<Velocity>& distribution
) const -> DensityDistribution<Velocity>
{
    const Float density{distribution.density()};
    const Vector<Float, Velocity::dimension()> momentum{distribution.momentum()};
    const Vector<Float, Velocity::dimension()> velocity{
        DensityDistribution<Velocity>::velocity(density, momentum)
    };

    const DensityDistribution<Velocity> equilibriumDistribution{
        Equilibrium::compute(density, velocity)
    };
    DensityDistribution<Velocity> postCollisionDistribution;

    for (Count dof = 0; dof < Velocity::size(); ++dof)
    {
        postCollisionDistribution[dof] = oneMinusRelaxationFactor_ * distribution[dof] +
                                         relaxationFactor_ * equilibriumDistribution[dof];
    }

    return postCollisionDistribution;
}
