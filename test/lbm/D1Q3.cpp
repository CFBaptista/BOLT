#include "lbm/D1Q3.hpp"

#include <numeric>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("D1Q3 lattice model properties")
{
    GIVEN("A D1Q3 lattice model")
    {
        using Model = D1Q3<float>;

        const auto expectedDimension{1};
        const auto expectedSize{3};
        const auto expectedVelocities = std::array<std::array<int, 1>, 3>{
            std::array<int, 1>{0}, std::array<int, 1>{1}, std::array<int, 1>{-1}
        };
        const auto expectedWeights = std::array<float, 3>{4.0F / 6, 1.0F / 6, 1.0F / 6};

        WHEN("Getting the dimension")
        {
            const auto dimension = Model::dimension();

            THEN("The dimension is 1")
            {
                CHECK(dimension == expectedDimension);
            }
        }

        WHEN("Getting the size")
        {
            const auto size = Model::size();

            THEN("The size is 3")
            {
                CHECK(size == expectedSize);
            }
        }

        WHEN("Getting the velocities")
        {
            const auto velocities = Model::velocities();

            THEN("The 3 velocities are correct")
            {
                CHECK(velocities.size() == expectedVelocities.size());
                CHECK(velocities == expectedVelocities);
            }

            THEN("Sum of velocities is zero")
            {
                int sum{0};
                for (const auto& velocity : velocities)
                {
                    sum += velocity[0];
                }

                CHECK(sum == 0);
            }
        }

        WHEN("Getting the weights")
        {
            const auto weights = Model::weights();

            THEN("The 3 weights are correct")
            {
                CHECK(weights.size() == expectedWeights.size());
                CHECK(weights == expectedWeights);
                CHECK(std::accumulate(weights.begin(), weights.end(), 0.0) == Catch::Approx(1.0));
            }
        }
    }
}
