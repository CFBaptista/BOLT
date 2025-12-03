#include <array>
#include <cstddef>
#include <functional>
#include <numeric>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/D3Q27.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("D3Q27 lattice model properties")
{
    GIVEN("A D3Q27 lattice model")
    {
        using Model = D3Q27<float>;

        std::move_only_function<std::size_t()> model_dimension = &Model::dimension;
        std::move_only_function<std::size_t()> model_size = &Model::size;
        std::move_only_function<std::array<std::array<int, Model::dimension()>, Model::size()>()>
            model_velocities = &Model::velocities;
        std::move_only_function<std::array<float, Model::size()>()> model_weights = &Model::weights;

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

        WHEN("Getting the dimension")
        {
            const auto dimension = model_dimension();

            THEN("The dimension is 3")
            {
                CHECK((dimension == expectedDimension));
            }
        }

        WHEN("Getting the size")
        {
            const auto size = model_size();

            THEN("The size is 27")
            {
                CHECK((size == expectedSize));
            }
        }

        WHEN("Getting the velocities")
        {
            const auto velocities = model_velocities();

            THEN("The 27 velocities are correct")
            {
                CHECK((velocities.size() == expectedVelocities.size()));
                CHECK((velocities == expectedVelocities));
            }

            THEN("Sum of velocities is zero")
            {
                std::array<int, 3> sum{0, 0, 0};
                for (const auto& velocity : velocities)
                {
                    sum[0] += velocity[0];
                    sum[1] += velocity[1];
                    sum[2] += velocity[2];
                }

                CHECK((sum == std::array<int, 3>{0, 0, 0}));
            }
        }

        WHEN("Getting the weights")
        {
            const auto weights = model_weights();

            THEN("The 27 weights are correct")
            {
                CHECK((weights.size() == expectedWeights.size()));
                CHECK((weights == expectedWeights));
                CHECK((std::accumulate(weights.begin(), weights.end(), 0.0) == Catch::Approx(1.0)));
            }
        }
    }
}
