#include "lbm/D2Q9.hpp"

#include <array>
#include <cstddef>
#include <functional>
#include <numeric>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("D2Q9 lattice model properties")
{
    GIVEN("A D2Q9 lattice model")
    {
        using Model = D2Q9<float>;

        std::move_only_function<std::size_t()> model_dimension = &Model::dimension;
        std::move_only_function<std::size_t()> model_size = &Model::size;
        std::move_only_function<std::array<std::array<int, Model::dimension()>, Model::size()>()>
            model_velocities = &Model::velocities;
        std::move_only_function<std::array<float, Model::size()>()> model_weights = &Model::weights;

        const auto expectedDimension{2};
        const auto expectedSize{9};
        const auto expectedVelocities = std::array<std::array<int, 2>, 9>{
            std::array<int, 2>{0, 0},  std::array<int, 2>{1, 0},   std::array<int, 2>{0, 1},
            std::array<int, 2>{-1, 0}, std::array<int, 2>{0, -1},  std::array<int, 2>{1, 1},
            std::array<int, 2>{-1, 1}, std::array<int, 2>{-1, -1}, std::array<int, 2>{1, -1}
        };
        const auto expectedWeights =
            std::array<float, 9>{4.0F / 9,  1.0F / 9,  1.0F / 9,  1.0F / 9, 1.0F / 9,
                                 1.0F / 36, 1.0F / 36, 1.0F / 36, 1.0F / 36};

        WHEN("Getting the dimension")
        {
            const auto dimension = model_dimension();

            THEN("The dimension is 2")
            {
                CHECK((dimension == expectedDimension));
            }
        }

        WHEN("Getting the size")
        {
            const auto size = model_size();

            THEN("The size is 9")
            {
                CHECK((size == expectedSize));
            }
        }

        WHEN("Getting the velocities")
        {
            const auto velocities = model_velocities();

            THEN("The 9 velocities are correct")
            {
                CHECK((velocities.size() == expectedVelocities.size()));
                CHECK((velocities == expectedVelocities));
            }

            THEN("Sum of velocities is zero")
            {
                std::array<int, 2> sum{0, 0};
                for (const auto& velocity : velocities)
                {
                    sum[0] += velocity[0];
                    sum[1] += velocity[1];
                }

                CHECK((sum == std::array<int, 2>{0, 0}));
            }
        }

        WHEN("Getting the weights")
        {
            const auto weights = model_weights();

            THEN("The 9 weights are correct")
            {
                CHECK((weights.size() == expectedWeights.size()));
                CHECK((weights == expectedWeights));
                CHECK((std::accumulate(weights.begin(), weights.end(), 0.0) == Catch::Approx(1.0)));
            }
        }
    }
}
