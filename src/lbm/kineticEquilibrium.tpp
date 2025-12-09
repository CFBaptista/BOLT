#include <array>
#include <cstdlib>
#include <numeric>

#include "lbm/DensityDistribution.hpp"
#include "lbm/VelocitySetBase.hpp"

template <VelocitySet Set>
auto maxwellEquilibriumSecondOrder(
    const typename Set::Real& density,
    const std::array<typename Set::Real, Set::dimension()>& velocity
) -> DensityDistribution<Set>
{
    using Real = typename Set::Real;

    const Real half{static_cast<Real>(0.5)};
    const Real halfMachSquared =
        half * Set::soundSpeedInverseSquared() *
        std::inner_product(
            velocity.begin(), velocity.end(), velocity.begin(), static_cast<Real>(0)
        );

    DensityDistribution<Set> equilibrium;

    for (std::size_t dof = 0; dof < Set::size(); ++dof)
    {
        const Real tmp = Set::soundSpeedInverseSquared() * std::inner_product(
                                                               velocity.begin(), velocity.end(),
                                                               Set::velocities()[dof].begin(),
                                                               static_cast<Real>(0)
                                                           );

        equilibrium[dof] = Set::weights()[dof] * density *
                           (static_cast<Real>(1) + tmp + half * tmp * tmp - halfMachSquared);
    }

    return equilibrium;
}
