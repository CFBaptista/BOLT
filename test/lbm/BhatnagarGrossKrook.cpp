#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/BhatnagarGrossKrook.hpp"
#include "lbm/D2Q9.hpp"
#include "lbm/DiscreteMaxwellBoltzmann.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("Perform collision step using the Bhatnagar-Gross-Krook operator")
{
    GIVEN("A BGK collision operator with invalid parameters")
    {
        using Velocity = D2Q9<double>;
        using Float = Velocity::Float;
        using collisionOperator =
            BhatnagarGrossKrook<Velocity, DiscreteMaxwellBoltzmann<Velocity, 2>>;

        WHEN("The time step is zero")
        {
            const Float timeStep{0.0};
            const Float relaxationTime{1.0};

            THEN("An exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    collisionOperator(timeStep, relaxationTime), std::invalid_argument
                );
            }
        }

        WHEN("The time step is negative")
        {
            const Float timeStep{-1.0};
            const Float relaxationTime{1.0};

            THEN("An exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    collisionOperator(timeStep, relaxationTime), std::invalid_argument
                );
            }
        }

        WHEN("The relaxation time is zero")
        {
            const Float timeStep{1.0};
            const Float relaxationTime{0.0};

            THEN("An exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    collisionOperator(timeStep, relaxationTime), std::invalid_argument
                );
            }
        }

        WHEN("The relaxation time is negative")
        {
            const Float timeStep{1.0};
            const Float relaxationTime{-1.0};

            THEN("An exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    collisionOperator(timeStep, relaxationTime), std::invalid_argument
                );
            }
        }
    }

    GIVEN("A valid BGK collision operator and a density distribution")
    {
        using Velocity = D2Q9<double>;
        using Float = Velocity::Float;
        using CollisionOperator =
            BhatnagarGrossKrook<Velocity, DiscreteMaxwellBoltzmann<Velocity, 2>>;
        using Distribution = DensityDistribution<Velocity>;

        const Float timeStep{0.1};
        const Float relaxationTime{1.0};
        CollisionOperator collisionOperator(timeStep, relaxationTime);

        const Distribution initialDistribution{{0.5, 0.1, 0.2, 0.1, 0.05, 0.02, 0.01, 0.005, 0.003}
        };

        const Distribution expectedPostCollisionDistribution{
            {0.4919105713, 0.1007475484, 0.1977081422, 0.100214215, 0.0512414755, 0.0225293297,
             0.0133263608, 0.0060293297, 0.0042930274}
        };

        WHEN("Performing the collision step")
        {
            const Distribution postCollisionDistribution{
                collisionOperator.collide(initialDistribution)
            };

            THEN("The post-collision distribution is computed correctly")
            {

                for (Count i = 0; i < Velocity::size(); ++i)
                {
                    REQUIRE(
                        (postCollisionDistribution[i] ==
                         Catch::Approx(expectedPostCollisionDistribution[i]))
                    );
                }
            }

            THEN("The post-collision distribution is not equal to the initial distribution")
            {
                for (Count i = 0; i < Velocity::size(); ++i)
                {
                    REQUIRE((postCollisionDistribution[i] != Catch::Approx(initialDistribution[i]))
                    );
                }
            }

            THEN("The macroscopic density is conserved")
            {
                const Float initialDensity{initialDistribution.density()};
                const Float postCollisionDensity{postCollisionDistribution.density()};

                REQUIRE((postCollisionDensity == Catch::Approx(initialDensity)));
            }

            THEN("The macroscopic momentum is conserved")
            {
                const Vector<Float, Velocity::dimension()> initialMomentum{
                    initialDistribution.momentum()
                };
                const Vector<Float, Velocity::dimension()> postCollisionMomentum{
                    postCollisionDistribution.momentum()
                };

                for (Count dim = 0; dim < Velocity::dimension(); ++dim)
                {
                    REQUIRE(
                        (postCollisionMomentum.at(dim) == Catch::Approx(initialMomentum.at(dim)))
                    );
                }
            }
        }
    }
}
