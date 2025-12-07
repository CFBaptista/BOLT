#include <array>
#include <cstddef>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/D2Q9.hpp"
#include "lbm/DensityDistribution.hpp"
#include "lbm/kineticEquilibrium.hpp"

SCENARIO("Compute kinetic equilibrium distribution")
{
    GIVEN("A macroscopic quantities")
    {
        using Set = D2Q9<double>;
        using Distribution = DensityDistribution<Set>;

        const double density{1.225};
        const std::array<double, 2> velocity{3.0, 5.0};
        const double speedOfSoundSquared{1.0 / 3.0};

        const Distribution expectedEquilibrium{
            {-27.2222222222, 5.4444444444, 25.8611111111, 2.9944444444, 21.7777777778,
             18.7152777778, -0.2722222222, 17.0819444444, -0.6805555556}
        };

        WHEN("Computing the kinetic equilibrium distribution")
        {
            const Distribution equilibrium{
                maxwellEquilibriumSecondOrder<Set>(density, velocity, speedOfSoundSquared)
            };

            THEN("The computed values are correct")
            {
                for (std::size_t i = 0; i < Set::size(); ++i)
                {
                    REQUIRE((equilibrium[i] == Catch::Approx(expectedEquilibrium[i])));
                }
            }
        }
    }
}
