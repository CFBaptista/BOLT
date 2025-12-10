#include <array>
#include <cstddef>
#include <numeric>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/D2Q9.hpp"
#include "lbm/DensityDistribution.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("DensityDistribution container operations")
{
    GIVEN("A dimension, size and distribution data")
    {
        const std::size_t expectedDimension{D2Q9<double>::dimension()};
        const std::size_t expectedSize{D2Q9<double>::size()};
        const std::array<double, expectedSize> expectedDistributionData{1,  2,  3,  5, 8,
                                                                        13, 21, 34, 55};

        GIVEN("A non-const DensityDistribution")
        {
            DensityDistribution<D2Q9<double>> distribution{expectedDistributionData};

            WHEN("The distribution is queried for its dimension")
            {
                THEN("The dimension matches the expected value")
                {
                    REQUIRE((distribution.dimension() == expectedDimension));
                }
            }

            WHEN("The distribution is queried for its size")
            {
                THEN("The size matches the expected value")
                {
                    REQUIRE((distribution.size() == expectedSize));
                }
            }

            WHEN("The distribution is queried for its data")
            {
                THEN("The data matches the expected value")
                {
                    for (std::size_t i = 0; i < expectedSize; ++i)
                    {
                        REQUIRE((distribution[i] == expectedDistributionData.at(i)));
                    }
                }
            }

            WHEN("The distribution data is updated")
            {
                const std::size_t index{3};
                const double value{1.23};
                distribution[index] = value;

                THEN("The updated value is reflected in the distribution")
                {
                    REQUIRE((distribution[index] == value));
                }
            }
        }

        GIVEN("A const DensityDistribution")
        {
            const DensityDistribution<D2Q9<double>> distribution{expectedDistributionData};

            WHEN("The distribution is queried for its data")
            {
                THEN("The data matches the expected value")
                {
                    for (std::size_t i = 0; i < expectedSize; ++i)
                    {
                        REQUIRE((distribution[i] == expectedDistributionData.at(i)));
                    }
                }
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("Calculating macroscopic quantities from a density distribution")
{
    GIVEN("A density distribution")
    {
        const std::size_t expectedDimension{D2Q9<double>::dimension()};
        const std::size_t expectedSize{D2Q9<double>::size()};
        const std::array<double, expectedSize> expectedDistributionData{1,  2,  3,  5, 8,
                                                                        13, 21, 34, 55};

        const double expectedDensity =
            std::accumulate(expectedDistributionData.begin(), expectedDistributionData.end(), 0.0);
        const std::array<double, 2> expectedMomentum{10, -60};
        const std::array<double, 2> expectedVelocity{
            expectedMomentum[0] / expectedDensity, expectedMomentum[1] / expectedDensity
        };

        const DensityDistribution<D2Q9<double>> distribution{expectedDistributionData};

        WHEN("The macroscopic density is calculated")
        {
            auto density = distribution.density();

            THEN("The calculated density matches the expected value")
            {
                REQUIRE((density == Catch::Approx(expectedDensity)));
            }
        }

        WHEN("The macroscopic momentum is calculated")
        {
            auto momentum = distribution.momentum();

            THEN("The calculated momentum matches the expected value")
            {
                for (std::size_t i = 0; i < expectedDimension; ++i)
                {
                    REQUIRE((momentum.at(i) == Catch::Approx(expectedMomentum.at(i))));
                }
            }
        }

        WHEN("The macroscopic velocity is calculated")
        {
            auto velocity =
                DensityDistribution<D2Q9<double>>::velocity(expectedDensity, expectedMomentum);

            THEN("The calculated velocity matches the expected value")
            {
                for (std::size_t i = 0; i < expectedDimension; ++i)
                {
                    REQUIRE((velocity.at(i) == Catch::Approx(expectedVelocity.at(i))));
                }
            }
        }
    }
}
