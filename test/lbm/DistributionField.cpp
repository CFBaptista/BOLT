#include <array>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/DistributionField.hpp"

SCENARIO("Assert static member data of DistributionField")
{
    GIVEN("The node count in the x direction")
    {
        const std::size_t nodeCountX = 3;

        THEN("The dimension of the DistributionField equals 1")
        {
            REQUIRE(DistributionField<nodeCountX>::dimension == 1);
        }

        THEN("The size of the DistributionField equals the product of the node counts")
        {
            REQUIRE(DistributionField<nodeCountX>::size == nodeCountX);
        }

        THEN("The shape of the DistributionField equals the node count")
        {
            REQUIRE(DistributionField<nodeCountX>::shape[0] == nodeCountX);
        }
    }

    GIVEN("The node count in the x and y directions")
    {
        const std::size_t nodeCountX = 3;
        const std::size_t nodeCountY = 4;

        THEN("The dimension of the DistributionField equals 2")
        {
            REQUIRE(DistributionField<nodeCountX, nodeCountY>::dimension == 2);
        }

        THEN("The size of the DistributionField equals the product of the node counts")
        {
            REQUIRE(DistributionField<nodeCountY, nodeCountX>::size == nodeCountX * nodeCountY);
        }

        THEN("The shape of the DistributionField equals the node counts")
        {
            REQUIRE(DistributionField<nodeCountY, nodeCountX>::shape[0] == nodeCountY);
            REQUIRE(DistributionField<nodeCountY, nodeCountX>::shape[1] == nodeCountX);
        }
    }

    GIVEN("The node count in the x, y and z directions")
    {
        const std::size_t nodeCountX = 3;
        const std::size_t nodeCountY = 4;
        const std::size_t nodeCountZ = 5;

        THEN("The dimension of the DistributionField equals 3")
        {
            REQUIRE(DistributionField<nodeCountZ, nodeCountY, nodeCountX>::dimension == 3);
        }

        THEN("The size of the DistributionField equals the product of the node counts")
        {
            REQUIRE(
                DistributionField<nodeCountZ, nodeCountY, nodeCountX>::size ==
                nodeCountX * nodeCountY * nodeCountZ
            );
        }

        THEN("The shape of the DistributionField equals the node counts")
        {
            REQUIRE(DistributionField<nodeCountZ, nodeCountY, nodeCountX>::shape[0] == nodeCountZ);
            REQUIRE(DistributionField<nodeCountZ, nodeCountY, nodeCountX>::shape[1] == nodeCountY);
            REQUIRE(DistributionField<nodeCountZ, nodeCountY, nodeCountX>::shape[2] == nodeCountX);
        }
    }
}

SCENARIO("Linear and Cartesian indexing of a DistributionField are consistent")
{
    GIVEN("A 2D DistributionField with node counts in the x and y directions")
    {
        const std::size_t nodeCountX = 3;
        const std::size_t nodeCountY = 4;
        DistributionField<nodeCountY, nodeCountX> distributionField;

        WHEN("Assigning a value to each node using linear indexing")
        {
            for (std::size_t index = 0; index < nodeCountX * nodeCountY; ++index)
            {
                distributionField[index] = static_cast<double>(index);
            }

            THEN(
                "The value at each node accessed using Cartesian indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t indexY = 0; indexY < nodeCountY; ++indexY)
                {
                    for (std::size_t indexX = 0; indexX < nodeCountX; ++indexX)
                    {
                        const std::size_t linearIndex = (indexY * nodeCountX) + indexX;
                        REQUIRE(
                            distributionField[linearIndex] == distributionField[indexY, indexX]
                        );
                    }
                }
            }
        }

        WHEN("Assigning a value to each node using Cartesian indexing")
        {
            for (std::size_t indexY = 0; indexY < nodeCountY; ++indexY)
            {
                for (std::size_t indexX = 0; indexX < nodeCountX; ++indexX)
                {
                    distributionField[indexY, indexX] = static_cast<double>(indexX + indexY);
                }
            }

            THEN(
                "The value at each node accessed using linear indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t index = 0; index < nodeCountX * nodeCountY; ++index)
                {
                    const std::size_t indexY = index / nodeCountX;
                    const std::size_t indexX = index % nodeCountX;
                    REQUIRE(distributionField[index] == distributionField[indexY, indexX]);
                }
            }
        }
    }
}
