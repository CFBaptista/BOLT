#include <array>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/DistributionField.hpp"

class FakeD1Q3
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 1;
    static constexpr std::size_t size = 3;
    static constexpr std::array<std::array<int, dimension>, size> velocities{};
    static constexpr std::array<double, size> weights{};
    static constexpr double sound_speed_inverse_squared{};
};

class FakeD2Q9
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 9;
    static constexpr std::array<std::array<int, dimension>, size> velocities{};
    static constexpr std::array<double, size> weights{};
    static constexpr double sound_speed_inverse_squared{};
};

class FakeD3Q27
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 3;
    static constexpr std::size_t size = 27;
    static constexpr std::array<std::array<int, dimension>, size> velocities{};
    static constexpr std::array<double, size> weights{};
    static constexpr double sound_speed_inverse_squared{};
};

SCENARIO("Verify intrinsic properties of a distribution field with specified shape")
{
    GIVEN("A node count in a single direction")
    {
        const std::size_t size_x = 3;

        THEN("The dimension of the distribution field equals 1")
        {
            REQUIRE(DistributionField<FakeD1Q3, size_x>::dimension == 1);
        }

        THEN("The size of the distribution field equals the node count")
        {
            REQUIRE(DistributionField<FakeD1Q3, size_x>::size == size_x);
        }

        THEN("The shape of the distribution field equals the node count")
        {
            REQUIRE(DistributionField<FakeD1Q3, size_x>::shape[0] == size_x);
        }
    }

    GIVEN("Node counts in two directions")
    {
        const std::size_t size_x = 3;
        const std::size_t size_y = 4;

        THEN("The dimension of the distribution field equals 2")
        {
            REQUIRE(DistributionField<FakeD2Q9, size_y, size_x>::dimension == 2);
        }

        THEN(
            "The size of the distribution field equals the product of the node counts in each "
            "direction"
        )
        {
            REQUIRE(DistributionField<FakeD2Q9, size_y, size_x>::size == size_x * size_y);
        }

        THEN("The shape of the distribution field equals the node counts in each direction")
        {
            REQUIRE(DistributionField<FakeD2Q9, size_y, size_x>::shape[0] == size_y);
            REQUIRE(DistributionField<FakeD2Q9, size_y, size_x>::shape[1] == size_x);
        }
    }

    GIVEN("Node counts in three directions")
    {
        const std::size_t size_x = 3;
        const std::size_t size_y = 4;
        const std::size_t size_z = 5;

        THEN("The dimension of the distribution field equals 3")
        {
            REQUIRE(DistributionField<FakeD3Q27, size_z, size_y, size_x>::dimension == 3);
        }

        THEN(
            "The size of the distribution field equals the product of the node counts in each "
            "direction"
        )
        {
            REQUIRE(
                DistributionField<FakeD3Q27, size_z, size_y, size_x>::size ==
                size_x * size_y * size_z
            );
        }

        THEN("The shape of the distribution field equals the node counts in each direction")
        {
            REQUIRE(DistributionField<FakeD3Q27, size_z, size_y, size_x>::shape[0] == size_z);
            REQUIRE(DistributionField<FakeD3Q27, size_z, size_y, size_x>::shape[1] == size_y);
            REQUIRE(DistributionField<FakeD3Q27, size_z, size_y, size_x>::shape[2] == size_x);
        }
    }
}

SCENARIO("Linear and Cartesian indexing of a distribution field is consistent")
{
    GIVEN("A 2D distribution field")
    {
        const std::size_t size_x = 3;
        const std::size_t size_y = 4;
        DistributionField<FakeD2Q9, size_y, size_x> distributionField;

        WHEN("Assigning a value to each node using linear indexing")
        {
            for (std::size_t index = 0; index < size_x * size_y; ++index)
            {
                distributionField[index] = static_cast<double>(index);
            }

            THEN(
                "The value at each node accessed using Cartesian indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t index_y = 0; index_y < size_y; ++index_y)
                {
                    for (std::size_t index_x = 0; index_x < size_x; ++index_x)
                    {
                        const std::size_t index = (index_y * size_x) + index_x;

                        REQUIRE(distributionField[index] == distributionField[index_y, index_x]);
                    }
                }
            }
        }

        WHEN("Assigning a value to each node using Cartesian indexing")
        {
            for (std::size_t index_y = 0; index_y < size_y; ++index_y)
            {
                for (std::size_t index_x = 0; index_x < size_x; ++index_x)
                {
                    distributionField[index_y, index_x] = static_cast<double>(index_x + index_y);
                }
            }

            THEN(
                "The value at each node accessed using linear indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t index = 0; index < size_x * size_y; ++index)
                {
                    const std::size_t index_x = index % size_x;
                    const std::size_t index_y = index / size_x;

                    REQUIRE(distributionField[index] == distributionField[index_y, index_x]);
                }
            }
        }
    }

    GIVEN("A 3D DistributionField")
    {
        const std::size_t size_x = 3;
        const std::size_t size_y = 4;
        const std::size_t size_z = 5;
        DistributionField<FakeD3Q27, size_z, size_y, size_x> distributionField;

        WHEN("Assigning a value to each node using linear indexing")
        {
            for (std::size_t index = 0; index < size_x * size_y * size_z; ++index)
            {
                distributionField[index] = static_cast<double>(index);
            }

            THEN(
                "The value at each node accessed using Cartesian indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t index_z = 0; index_z < size_z; ++index_z)
                {
                    for (std::size_t index_y = 0; index_y < size_y; ++index_y)
                    {
                        for (std::size_t index_x = 0; index_x < size_x; ++index_x)
                        {
                            const std::size_t index =
                                (index_z * size_y * size_x) + (index_y * size_x) + index_x;

                            REQUIRE(
                                distributionField[index] ==
                                distributionField[index_z, index_y, index_x]
                            );
                        }
                    }
                }
            }
        }

        WHEN("Assigning a value to each node using Cartesian indexing")
        {
            for (std::size_t index_z = 0; index_z < size_z; ++index_z)
            {
                for (std::size_t index_y = 0; index_y < size_y; ++index_y)
                {
                    for (std::size_t index_x = 0; index_x < size_x; ++index_x)
                    {
                        distributionField[index_z, index_y, index_x] =
                            static_cast<double>(index_x + index_y + index_z);
                    }
                }
            }

            THEN(
                "The value at each node accessed using linear indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t index = 0; index < size_x * size_y * size_z; ++index)
                {
                    const std::size_t index_x = index % size_x;
                    const std::size_t index_y = (index / size_x) % size_y;
                    const std::size_t index_z = index / (size_y * size_x);

                    REQUIRE(
                        distributionField[index] == distributionField[index_z, index_y, index_x]
                    );
                }
            }
        }
    }
}
