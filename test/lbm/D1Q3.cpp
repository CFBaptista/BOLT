#include <array>
#include <cstddef>
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

        std::move_only_function<std::size_t()> model_dimension = &Set::dimension;
        std::move_only_function<std::size_t()> model_size = &Set::size;
        std::move_only_function<std::array<std::array<float, Set::dimension()>, Set::size()>()>
            model_velocities = &Set::velocities;
        std::move_only_function<std::array<float, Set::size()>()> model_weights = &Set::weights;
        std::move_only_function<float()> model_soundSpeedInverseSquared =
            &Set::soundSpeedInverseSquared;

        const auto expectedDimension{1};
        const auto expectedSize{3};
        const auto expectedVelocities = std::array<std::array<float, 1>, 3>{
            std::array<float, 1>{0}, std::array<float, 1>{1}, std::array<float, 1>{-1}
        };
        const auto expectedWeights = std::array<float, 3>{4.0F / 6, 1.0F / 6, 1.0F / 6};
        const auto expectedSoundSpeedInverseSquared{3.0F};

        WHEN("Getting the dimension")
        {
            const auto dimension = model_dimension();

            THEN("The dimension is 1")
            {
                REQUIRE((dimension == expectedDimension));
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
                float sum{0.0F};
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
