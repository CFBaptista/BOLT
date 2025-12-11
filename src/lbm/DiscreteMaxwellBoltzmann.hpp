#pragma once

#include "lbm/DensityDistribution.hpp"
#include "lbm/EquilibriumDistributionBase.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Set, Count Order>
class DiscreteMaxwellBoltzmann : public EquilibriumDistributionBase
{
public:
    /**
     * @fn compute
     *
     * @brief Computes an approximation of the Maxwell-Boltzmann equilibrium distribution
     * for a given velocity set.
     *
     * @tparam Set The velocity set type.
     * @param density The macroscopic density.
     * @param velocity The macroscopic velocity.
     * @return The computed equilibrium distribution.
     */
    static auto compute(
        const typename Set::Real& density,
        const Vector<typename Set::Real, Set::dimension()>& velocity
    ) -> DensityDistribution<Set>;
};

/// Specialization for second-order equilibrium
template <VelocitySet Set>
class DiscreteMaxwellBoltzmann<Set, 2>
{
public:
    static auto compute(
        const typename Set::Real& density,
        const Vector<typename Set::Real, Set::dimension()>& velocity
    ) -> DensityDistribution<Set>;
};

#include "lbm/DiscreteMaxwellBoltzmann.tpp"
