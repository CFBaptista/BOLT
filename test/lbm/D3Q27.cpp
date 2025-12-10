#include <array>
#include <cstddef>
#include <functional>
#include <numeric>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/D3Q27.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("D3Q27 velocity set properties")
{
    GIVEN("A D3Q27 velocity set")
    {
        using Set = D3Q27<float>;

        std::move_only_function<std::size_t()> model_dimension = &Set::dimension;
        std::move_only_function<std::size_t()> model_size = &Set::size;
        std::move_only_function<std::array<std::array<int, Set::dimension()>, Set::size()>()>
            model_velocities = &Set::velocities;
        std::move_only_function<std::array<float, Set::size()>()> model_weights = &Set::weights;
        std::move_only_function<float()> model_soundSpeedInverseSquared =
            &Set::soundSpeedInverseSquared;

        const auto expectedDimension{3};
        const auto expectedSize{27};
        const auto expectedVelocities = std::array<std::array<int, 3>, 27>{
            std::array<int, 3>{0, 0, 0},   std::array<int, 3>{1, 0, 0},
            std::array<int, 3>{-1, 0, 0},  std::array<int, 3>{0, 1, 0},
            std::array<int, 3>{0, -1, 0},  std::array<int, 3>{0, 0, 1},
            std::array<int, 3>{0, 0, -1},  std::array<int, 3>{1, 1, 0},
            std::array<int, 3>{-1, 1, 0},  std::array<int, 3>{1, -1, 0},
            std::array<int, 3>{-1, -1, 0}, std::array<int, 3>{1, 0, 1},
            std::array<int, 3>{-1, 0, 1},  std::array<int, 3>{1, 0, -1},
            std::array<int, 3>{-1, 0, -1}, std::array<int, 3>{0, 1, 1},
            std::array<int, 3>{0, -1, 1},  std::array<int, 3>{0, 1, -1},
            std::array<int, 3>{0, -1, -1}, std::array<int, 3>{1, 1, 1},
            std::array<int, 3>{-1, 1, 1},  std::array<int, 3>{1, -1, 1},
            std::array<int, 3>{-1, -1, 1}, std::array<int, 3>{1, 1, -1},
            std::array<int, 3>{-1, 1, -1}, std::array<int, 3>{1, -1, -1},
            std::array<int, 3>{-1, -1, -1}
        };
        const auto expectedWeights = std::array<float, 27>{
            8.0F / 27,  2.0F / 27,  2.0F / 27,  2.0F / 27,  2.0F / 27,  2.0F / 27,  2.0F / 27,
            1.0F / 54,  1.0F / 54,  1.0F / 54,  1.0F / 54,  1.0F / 54,  1.0F / 54,  1.0F / 54,
            1.0F / 54,  1.0F / 54,  1.0F / 54,  1.0F / 54,  1.0F / 54,  1.0F / 216, 1.0F / 216,
            1.0F / 216, 1.0F / 216, 1.0F / 216, 1.0F / 216, 1.0F / 216, 1.0F / 216
        };
        const auto expectedSoundSpeedInverseSquared{3.0F};

        WHEN("Getting the dimension")
        {
            const auto dimension = model_dimension();

            THEN("The dimension is 3")
            {
                REQUIRE((dimension == expectedDimension));
            }
        }

        WHEN("Getting the size")
        {
            const auto size = model_size();

            THEN("The size is 27")
            {
                REQUIRE((size == expectedSize));
            }
        }

        WHEN("Getting the velocities")
        {
            const auto velocities = model_velocities();

            THEN("The 27 velocities are correct")
            {
                REQUIRE((velocities.size() == expectedVelocities.size()));
                REQUIRE((velocities == expectedVelocities));
            }

            THEN("Sum of velocities is zero")
            {
                std::array<float, 3> sum{0, 0, 0};
                for (const auto& velocity : velocities)
                {
                    sum[0] += velocity[0];
                    sum[1] += velocity[1];
                    sum[2] += velocity[2];
                }

                REQUIRE((sum == std::array<float, 3>{0, 0, 0}));
            }
        }

        WHEN("Getting the weights")
        {
            const auto weights = model_weights();

            THEN("The 27 weights are correct")
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
