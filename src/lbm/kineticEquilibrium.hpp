#include <array>
#include <cstdlib>

#include "lbm/DensityDistribution.hpp"
#include "lbm/VelocitySetBase.hpp"

/**
 * @fn maxwellEquilibriumSecondOrder
 *
 * @brief Computes the second-order approximation of the Maxwell-Boltzmann equilibrium distribution
 * for a given velocity set.
 *
 * @tparam Set The velocity set type.
 * @param density The macroscopic density.
 * @param velocity The macroscopic velocity.
 * @param speedOfSoundSquared The square of the speed of sound.
 * @return The computed equilibrium distribution.
 */
template <VelocitySet Set>
auto maxwellEquilibriumSecondOrder(
    const typename Set::Real& density,
    const std::array<typename Set::Real, Set::dimension()>& velocity
) -> DensityDistribution<Set>;

#include "lbm/kineticEquilibrium.tpp"
