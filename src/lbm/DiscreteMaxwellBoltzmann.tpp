#pragma once

#include <cstdlib>
#include <numeric>

#include "lbm/DensityDistribution.hpp"
#include "lbm/DiscreteMaxwellBoltzmann.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Velocity>
auto DiscreteMaxwellBoltzmann<Velocity, 2>::compute(
    const typename Velocity::Float& density,
    const Vector<typename Velocity::Float, Velocity::dimension()>& velocity
) -> DensityDistribution<Velocity>
{
    using Float = typename Velocity::Float;

    const Float half{static_cast<Float>(0.5)};
    const Float halfMachSquared =
        half * Velocity::soundSpeedInverseSquared() *
        std::inner_product(
            velocity.begin(), velocity.end(), velocity.begin(), static_cast<Float>(0)
        );

    DensityDistribution<Velocity> equilibrium;

    for (Count dof = 0; dof < Velocity::size(); ++dof)
    {
        const Float tmp = Velocity::soundSpeedInverseSquared() *
                          std::inner_product(
                              velocity.begin(), velocity.end(), Velocity::velocities()[dof].begin(),
                              static_cast<Float>(0)
                          );

        equilibrium[dof] = Velocity::weights()[dof] * density *
                           (static_cast<Float>(1) + tmp + half * tmp * tmp - halfMachSquared);
    }

    return equilibrium;
}
