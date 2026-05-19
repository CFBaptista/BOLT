#include <array>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "lbm/DistributionField.hpp"

SCENARIO("Verify intrinsic properties of a distribution field with specified shape")
{
    GIVEN("A node count in a single direction")
    {
        const std::size_t nx = 3;

        THEN("The dimension of the distribution field equals 1")
        {
            REQUIRE(DistributionField<D1Q3<double>, nx>::dimension == 1);
        }

        THEN("The size of the distribution field equals the node count")
        {
            REQUIRE(DistributionField<D1Q3<double>, nx>::size == nx);
        }

        THEN("The shape of the distribution field equals the node count")
        {
            REQUIRE(DistributionField<D1Q3<double>, nx>::shape[0] == nx);
        }
    }

    GIVEN("Node counts in two directions")
    {
        const std::size_t nx = 3;
        const std::size_t ny = 4;

        THEN("The dimension of the distribution field equals 2")
        {
            REQUIRE(DistributionField<D2Q9<double>, ny, nx>::dimension == 2);
        }

        THEN(
            "The size of the distribution field equals the product of the node counts in each "
            "direction"
        )
        {
            REQUIRE(DistributionField<D2Q9<double>, ny, nx>::size == nx * ny);
        }

        THEN("The shape of the distribution field equals the node counts in each direction")
        {
            REQUIRE(DistributionField<D2Q9<double>, ny, nx>::shape[0] == ny);
            REQUIRE(DistributionField<D2Q9<double>, ny, nx>::shape[1] == nx);
        }
    }

    GIVEN("Node counts in three directions")
    {
        const std::size_t nx = 3;
        const std::size_t ny = 4;
        const std::size_t nz = 5;

        THEN("The dimension of the distribution field equals 3")
        {
            REQUIRE(DistributionField<D3Q27<double>, nz, ny, nx>::dimension == 3);
        }

        THEN(
            "The size of the distribution field equals the product of the node counts in each "
            "direction"
        )
        {
            REQUIRE(DistributionField<D3Q27<double>, nz, ny, nx>::size == nx * ny * nz);
        }

        THEN("The shape of the distribution field equals the node counts in each direction")
        {
            REQUIRE(DistributionField<D3Q27<double>, nz, ny, nx>::shape[0] == nz);
            REQUIRE(DistributionField<D3Q27<double>, nz, ny, nx>::shape[1] == ny);
            REQUIRE(DistributionField<D3Q27<double>, nz, ny, nx>::shape[2] == nx);
        }
    }
}

SCENARIO("Linear and Cartesian indexing of a distribution field is consistent")
{
    GIVEN("A 2D distribution field")
    {
        const std::size_t nx = 3;
        const std::size_t ny = 4;
        DistributionField<D2Q9<double>, ny, nx> distributionField;

        WHEN("Assigning a value to each node using linear indexing")
        {
            for (std::size_t i = 0; i < nx * ny; ++i)
            {
                distributionField[i] = static_cast<double>(i);
            }

            THEN(
                "The value at each node accessed using Cartesian indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t iy = 0; iy < ny; ++iy)
                {
                    for (std::size_t ix = 0; ix < nx; ++ix)
                    {
                        const std::size_t i = (iy * nx) + ix;

                        REQUIRE(distributionField[i] == distributionField[iy, ix]);
                    }
                }
            }
        }

        WHEN("Assigning a value to each node using Cartesian indexing")
        {
            for (std::size_t iy = 0; iy < ny; ++iy)
            {
                for (std::size_t ix = 0; ix < nx; ++ix)
                {
                    distributionField[iy, ix] = static_cast<double>(ix + iy);
                }
            }

            THEN(
                "The value at each node accessed using linear indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t i = 0; i < nx * ny; ++i)
                {
                    const std::size_t ix = i % nx;
                    const std::size_t iy = i / nx;

                    REQUIRE(distributionField[i] == distributionField[iy, ix]);
                }
            }
        }
    }

    GIVEN("A 3D DistributionField")
    {
        const std::size_t nx = 3;
        const std::size_t ny = 4;
        const std::size_t nz = 5;
        DistributionField<D3Q27<double>, nz, ny, nx> distributionField;

        WHEN("Assigning a value to each node using linear indexing")
        {
            for (std::size_t i = 0; i < nx * ny * nz; ++i)
            {
                distributionField[i] = static_cast<double>(i);
            }

            THEN(
                "The value at each node accessed using Cartesian indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t iz = 0; iz < nz; ++iz)
                {
                    for (std::size_t iy = 0; iy < ny; ++iy)
                    {
                        for (std::size_t ix = 0; ix < nx; ++ix)
                        {
                            const std::size_t i = (iz * ny * nx) + (iy * nx) + ix;

                            REQUIRE(distributionField[i] == distributionField[iz, iy, ix]);
                        }
                    }
                }
            }
        }

        WHEN("Assigning a value to each node using Cartesian indexing")
        {
            for (std::size_t iz = 0; iz < nz; ++iz)
            {
                for (std::size_t iy = 0; iy < ny; ++iy)
                {
                    for (std::size_t ix = 0; ix < nx; ++ix)
                    {
                        distributionField[iz, iy, ix] = static_cast<double>(ix + iy + iz);
                    }
                }
            }

            THEN(
                "The value at each node accessed using linear indexing matches the assigned "
                "value"
            )
            {
                for (std::size_t i = 0; i < nx * ny * nz; ++i)
                {
                    const std::size_t ix = i % nx;
                    const std::size_t iy = (i / nx) % ny;
                    const std::size_t iz = i / (ny * nx);

                    REQUIRE(distributionField[i] == distributionField[iz, iy, ix]);
                }
            }
        }
    }
}
