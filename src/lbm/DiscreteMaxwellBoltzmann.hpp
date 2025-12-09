#pragma once

#include <array>
#include <cstdlib>

#include "lbm/DensityDistribution.hpp"
#include "lbm/EquilibriumDistribution.hpp"
#include "lbm/VelocitySetBase.hpp"

template <VelocitySet Set, std::size_t Order>
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
        const std::array<typename Set::Real, Set::dimension()>& velocity
    ) -> DensityDistribution<Set>;
};

/// Specialization for second-order equilibrium
template <VelocitySet Set>
class DiscreteMaxwellBoltzmann<Set, 2>
{
public:
    static auto compute(
        const typename Set::Real& density,
        const std::array<typename Set::Real, Set::dimension()>& velocity
    ) -> DensityDistribution<Set>;
};

#include "lbm/DiscreteMaxwellBoltzmann.tpp"
