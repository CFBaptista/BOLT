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
            REQUIRE(DistributionField<nodeCountX, nodeCountY>::size == nodeCountX * nodeCountY);
        }

        THEN("The shape of the DistributionField equals the node counts")
        {
            REQUIRE(DistributionField<nodeCountX, nodeCountY>::shape[0] == nodeCountX);
            REQUIRE(DistributionField<nodeCountX, nodeCountY>::shape[1] == nodeCountY);
        }
    }

    GIVEN("The node count in the x, y and z directions")
    {
        const std::size_t nodeCountX = 3;
        const std::size_t nodeCountY = 4;
        const std::size_t nodeCountZ = 5;

        THEN("The dimension of the DistributionField equals 3")
        {
            REQUIRE(DistributionField<nodeCountX, nodeCountY, nodeCountZ>::dimension == 3);
        }

        THEN("The size of the DistributionField equals the product of the node counts")
        {
            REQUIRE(
                DistributionField<nodeCountX, nodeCountY, nodeCountZ>::size ==
                nodeCountX * nodeCountY * nodeCountZ
            );
        }

        THEN("The shape of the DistributionField equals the node counts")
        {
            REQUIRE(DistributionField<nodeCountX, nodeCountY, nodeCountZ>::shape[0] == nodeCountX);
            REQUIRE(DistributionField<nodeCountX, nodeCountY, nodeCountZ>::shape[1] == nodeCountY);
            REQUIRE(DistributionField<nodeCountX, nodeCountY, nodeCountZ>::shape[2] == nodeCountZ);
        }
    }
}
