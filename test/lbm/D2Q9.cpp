#include <functional>
#include <numeric>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/D2Q9.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("D2Q9 velocity set properties")
{
    GIVEN("A D2Q9 velocity set")
    {
        using Velocity = D2Q9<float>;

        std::move_only_function<Count()> model_dimension = &Velocity::dimension;
        std::move_only_function<Count()> model_size = &Velocity::size;
        std::move_only_function<Matrix<Index, Velocity::size(), Velocity::dimension()>()>
            model_velocities = &Velocity::velocities;
        std::move_only_function<Vector<float, Velocity::size()>()> model_weights =
            &Velocity::weights;
        std::move_only_function<float()> model_soundSpeedInverseSquared =
            &Velocity::soundSpeedInverseSquared;

        const auto expectedDimension{2};
        const auto expectedSize{9};
        const auto expectedVelocities = Matrix<Index, 9, 2>{
            Vector<Index, 2>{0, 0},  Vector<Index, 2>{1, 0},   Vector<Index, 2>{0, 1},
            Vector<Index, 2>{-1, 0}, Vector<Index, 2>{0, -1},  Vector<Index, 2>{1, 1},
            Vector<Index, 2>{-1, 1}, Vector<Index, 2>{-1, -1}, Vector<Index, 2>{1, -1}
        };
        const auto expectedWeights =
            Vector<float, 9>{4.0F / 9,  1.0F / 9,  1.0F / 9,  1.0F / 9, 1.0F / 9,
                             1.0F / 36, 1.0F / 36, 1.0F / 36, 1.0F / 36};
        const auto expectedSoundSpeedInverseSquared{3.0F};

        WHEN("Getting the dimension")
        {
            const auto dimension = model_dimension();

            THEN("The dimension is 2")
            {
                REQUIRE((dimension == expectedDimension));
            }
        }

        WHEN("Getting the size")
        {
            const auto size = model_size();

            THEN("The size is 9")
            {
                REQUIRE((size == expectedSize));
            }
        }

        WHEN("Getting the velocities")
        {
            const auto velocities = model_velocities();

            THEN("The 9 velocities are correct")
            {
                REQUIRE((velocities.size() == expectedVelocities.size()));
                REQUIRE((velocities == expectedVelocities));
            }

            THEN("Sum of velocities is zero")
            {
                Vector<Index, 2> sum{0, 0};
                for (const auto& velocity : velocities)
                {
                    sum[0] += velocity[0];
                    sum[1] += velocity[1];
                }

                REQUIRE((sum == Vector<Index, 2>{0, 0}));
            }
        }

        WHEN("Getting the weights")
        {
            const auto weights = model_weights();

            THEN("The 9 weights are correct")
            {
                REQUIRE((weights.size() == expectedWeights.size()));
                REQUIRE((weights == expectedWeights));
                REQUIRE((std::accumulate(weights.begin(), weights.end(), 0.0) == Catch::Approx(1.0))
                );
            }
        }

        WHEN("Getting the inverse of the speed of sound squared")
        {
            const auto soundSpeedInverseSquared = model_soundSpeedInverseSquared();

            THEN("The inverse of the speed of sound squared is correct")
            {
                REQUIRE((soundSpeedInverseSquared == expectedSoundSpeedInverseSquared));
            }
        }
    }
}
