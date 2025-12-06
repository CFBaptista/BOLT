#include <array>
#include <cstdlib>
#include <numeric>

#include "lbm/DensityDistribution.hpp"
#include "lbm/VelocitySetBase.hpp"

template <VelocitySet Set>
auto maxwellEquilibriumSecondOrder(
    const typename Set::Real& density,
    const std::array<typename Set::Real, Set::dimension()>& velocity,
    const typename Set::Real& speedOfSoundSquared
) -> DensityDistribution<Set>
{
    using Real = typename Set::Real;

    Real halfMachSquared = std::accumulate(
        velocity.begin(), velocity.end(), static_cast<Real>(0),
        [](Real sumOfSquares, Real u_i) { return sumOfSquares + u_i * u_i; }
    );
    halfMachSquared /= static_cast<Real>(2) * speedOfSoundSquared;

    DensityDistribution<Set> equilibrium;

    for (std::size_t dir = 0; dir < Set::size(); ++dir)
    {
        Real tmp{0};

        for (std::size_t dim = 0; dim < Set::dimension(); ++dim)
        {
            tmp += Set::velocities()[dir][dim] * velocity[dim];
        }
        tmp /= speedOfSoundSquared;

        equilibrium[dir] = Set::weights()[dir] * density *
                           (static_cast<Real>(1) + tmp + tmp * tmp - halfMachSquared);
    }

    return equilibrium;
}
