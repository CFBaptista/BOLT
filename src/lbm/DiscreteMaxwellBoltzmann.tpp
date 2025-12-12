#pragma once

#include <cstdlib>
#include <numeric>

#include "lbm/DensityDistribution.hpp"
#include "lbm/DiscreteMaxwellBoltzmann.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Set>
auto DiscreteMaxwellBoltzmann<Set, 2>::compute(
    const typename Set::Float& density,
    const Vector<typename Set::Float, Set::dimension()>& velocity
) -> DensityDistribution<Set>
{
    using Float = typename Set::Float;

    const Float half{static_cast<Float>(0.5)};
    const Float halfMachSquared =
        half * Set::soundSpeedInverseSquared() *
        std::inner_product(
            velocity.begin(), velocity.end(), velocity.begin(), static_cast<Float>(0)
        );

    DensityDistribution<Set> equilibrium;

    for (Count dof = 0; dof < Set::size(); ++dof)
    {
        const Float tmp = Set::soundSpeedInverseSquared() * std::inner_product(
                                                                velocity.begin(), velocity.end(),
                                                                Set::velocities()[dof].begin(),
                                                                static_cast<Float>(0)
                                                            );

        equilibrium[dof] = Set::weights()[dof] * density *
                           (static_cast<Float>(1) + tmp + half * tmp * tmp - halfMachSquared);
    }

    return equilibrium;
}
