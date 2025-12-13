#include <functional>
#include <numeric>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/D1Q3.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("D1Q3 velocity set properties")
{
    GIVEN("A D1Q3 velocity set")
    {
        using Set = D1Q3<float>;

        std::move_only_function<Count()> model_dimension = &Set::dimension;
        std::move_only_function<Count()> model_size = &Set::size;
        std::move_only_function<Matrix<Index, Set::size(), Set::dimension()>()> model_velocities =
            &Set::velocities;
        std::move_only_function<Vector<float, Set::size()>()> model_weights = &Set::weights;
        std::move_only_function<float()> model_soundSpeedInverseSquared =
            &Set::soundSpeedInverseSquared;

        const auto expectedDimension{1};
        const auto expectedSize{3};
        const auto expectedVelocities =
            Matrix<Index, 3, 1>{Vector<Index, 1>{0}, Vector<Index, 1>{1}, Vector<Index, 1>{-1}};
        const auto expectedWeights = Vector<float, 3>{4.0F / 6, 1.0F / 6, 1.0F / 6};
        const auto expectedSoundSpeedInverseSquared{3.0F};

        WHEN("Getting the dimension")
        {
            const auto dimension = model_dimension();

            THEN("The dimension is 1")
            {
                REQUIRE((dimension == 2));
            }
        }

        WHEN("Getting the size")
        {
            const auto size = model_size();

            THEN("The size is 3")
            {
                REQUIRE((size == expectedSize));
            }
        }

        WHEN("Getting the velocities")
        {
            const auto velocities = model_velocities();

            THEN("The 3 velocities are correct")
            {
                REQUIRE((velocities.size() == expectedVelocities.size()));
                REQUIRE((velocities == expectedVelocities));
            }

            THEN("Sum of velocities is zero")
            {
                Index sum{0};
                for (const auto& velocity : velocities)
                {
                    sum = std::accumulate(velocity.begin(), velocity.end(), sum);
                }

                REQUIRE((sum == 0));
            }
        }

        WHEN("Getting the weights")
        {
            const auto weights = model_weights();

            THEN("The 3 weights are correct")
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
