#pragma once

#include <stdexcept>

#include "lbm/BhatnagarGrossKrook.hpp"

template <VelocitySet Set, EquilibriumDistribution Equilibrium>
BhatnagarGrossKrook<Set, Equilibrium>::BhatnagarGrossKrook(
    const Real& timeStep,
    const Real& relaxationTime
)
    : timeStep_(timeStep), relaxationTime_(relaxationTime),
      relaxationFactor_(timeStep / relaxationTime),
      oneMinusRelaxationFactor_(static_cast<Real>(1) - relaxationFactor_)
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

template <VelocitySet Set, EquilibriumDistribution Equilibrium>
auto BhatnagarGrossKrook<Set, Equilibrium>::collide(const DensityDistribution<Set>& distribution
) const -> DensityDistribution<Set>
{
    const Real density{distribution.density()};
    const std::array<Real, Set::dimension()> momentum{distribution.momentum()};
    const std::array<Real, Set::dimension()> velocity{
        DensityDistribution<Set>::velocity(density, momentum)
    };

    const DensityDistribution<Set> equilibriumDistribution{Equilibrium::compute(density, velocity)};
    DensityDistribution<Set> postCollisionDistribution;

    for (std::size_t dof = 0; dof < Set::size(); ++dof)
    {
        postCollisionDistribution[dof] = oneMinusRelaxationFactor_ * distribution[dof] +
                                         relaxationFactor_ * equilibriumDistribution[dof];
    }

    return postCollisionDistribution;
}
