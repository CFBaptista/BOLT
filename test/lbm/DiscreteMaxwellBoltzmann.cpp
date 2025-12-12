#include <functional>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/D2Q9.hpp"
#include "lbm/DensityDistribution.hpp"
#include "lbm/DiscreteMaxwellBoltzmann.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("Compute kinetic equilibrium distribution")
{
    GIVEN("A macroscopic quantities")
    {
        using Set = D2Q9<double>;
        using Distribution = DensityDistribution<Set>;

        std::move_only_function<Distribution(const double&, const Vector<double, 2>&)>
            maxwell_compute = &DiscreteMaxwellBoltzmann<Set, 2>::compute;

        const double expectedDensity{1.225};
        const Vector<double, 2> expectedVelocity{3.0, 5.0};

        const Distribution expectedEquilibrium{
            {-27.2222222222, -0.0680555556, 10.5486111111, -2.5180555556, 6.4652777778,
             8.9152777778, -0.8847222222, 7.2819444444, -1.2930555556}
        };

        WHEN("Computing the kinetic equilibrium distribution")
        {
            const Distribution equilibrium{maxwell_compute(expectedDensity, expectedVelocity)};

            THEN("The computed values are correct")
            {
                for (Count i = 0; i < Set::size(); ++i)
                {
                    REQUIRE((equilibrium[i] == Catch::Approx(expectedEquilibrium[i])));
                }
            }

            WHEN("Computing the macroscopic density from the equilibrium distribution")
            {
                const double density{equilibrium.density()};

                THEN("The computed density matches the expected value")
                {
                    REQUIRE((density == Catch::Approx(expectedDensity)));
                }
            }

            WHEN("Computing the macroscopic momentum from the equilibrium distribution")
            {
                const auto momentum{equilibrium.momentum()};

                THEN("The computed momentum matches the expected value")
                {
                    for (Count dim = 0; dim < Set::dimension(); ++dim)
                    {
                        REQUIRE(
                            (momentum.at(dim) ==
                             Catch::Approx(expectedDensity * expectedVelocity.at(dim)))
                        );
                    }
                }
            }

            WHEN("Computing the macroscopic velocity from the equilibrium distribution")
            {
                const double density{equilibrium.density()};
                const auto momentum{equilibrium.momentum()};
                const auto velocity{Distribution::velocity(density, momentum)};

                THEN("The computed velocity matches the expected value")
                {
                    for (Count dim = 0; dim < Set::dimension(); ++dim)
                    {
                        REQUIRE((velocity.at(dim) == Catch::Approx(expectedVelocity.at(dim))));
                    }
                }
            }
        }
    }
}
