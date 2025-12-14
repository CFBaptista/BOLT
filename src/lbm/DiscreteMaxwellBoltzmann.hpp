#pragma once

#include "lbm/DensityDistribution.hpp"
#include "lbm/EquilibriumDistributionBase.hpp"
#include "lbm/VelocitySetBase.hpp"
#include "utils/aliases.hpp"

template <VelocitySet Velocity, Count Order>
class DiscreteMaxwellBoltzmann : public EquilibriumDistributionBase
{
public:
    /// The velocity set type.
    using VelocityType = Velocity;
    /// The order of the equilibrium approximation.
    static constexpr Count OrderType = Order;
    /// The floating-point type.
    using Float = typename Velocity::Float;

    /**
     * @fn compute
     *
     * @brief Computes an approximation of the Maxwell-Boltzmann equilibrium distribution
     * for a given velocity set.
     *
     * @tparam Velocity The velocity set type.
     * @param density The macroscopic density.
     * @param velocity The macroscopic velocity.
     * @return The computed equilibrium distribution.
     */
    static auto compute(
        const typename Velocity::Float& density,
        const Vector<typename Velocity::Float, Velocity::dimension()>& velocity
    ) -> DensityDistribution<Velocity>;
};

/// Specialization for second-order equilibrium
template <VelocitySet Velocity>
class DiscreteMaxwellBoltzmann<Velocity, 2>
{
public:
    static auto compute(
        const typename Velocity::Float& density,
        const Vector<typename Velocity::Float, Velocity::dimension()>& velocity
    ) -> DensityDistribution<Velocity>;
};

#include "lbm/DiscreteMaxwellBoltzmann.tpp"
