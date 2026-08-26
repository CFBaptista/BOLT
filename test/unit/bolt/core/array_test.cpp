#include <array>
#include <cstddef>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "bolt/core/array.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("array has correct static properties")
{
    GIVEN("A 1D array type with 3 elements")
    {
        constexpr std::size_t expected_size = 3;
        constexpr std::size_t expected_shape_0 = 3;
        constexpr std::size_t expected_alignment = 64;

        THEN("The size, shape, and alignment match the template parameters")
        {
            REQUIRE(bolt::array<double, 3>::size == expected_size);
            REQUIRE(bolt::array<double, 3>::shape[0] == expected_shape_0);
            static_assert(bolt::array<double, 3>::alignment == expected_alignment);
        }
    }

    GIVEN("A 2D array type with 2 rows and 3 columns")
    {
        constexpr std::size_t expected_size = 6;
        constexpr std::array<std::size_t, 2> expected_shape = {2, 3};

        THEN("The size and shape match the template parameters")
        {
            REQUIRE(bolt::array<double, 2, 3>::size == expected_size);
            for (std::size_t i = 0; i < expected_shape.size(); ++i)
            {
                REQUIRE(bolt::array<double, 2, 3>::shape[i] == expected_shape[i]);
            }
        }
    }

    GIVEN("A 3D array type with 2x3x4 dimensions")
    {
        constexpr std::size_t expected_size = 24;
        constexpr std::array<std::size_t, 3> expected_shape = {2, 3, 4};

        THEN("The size and shape match the template parameters")
        {
            REQUIRE(bolt::array<double, 2, 3, 4>::size == expected_size);
            for (std::size_t i = 0; i < expected_shape.size(); ++i)
            {
                REQUIRE(bolt::array<double, 2, 3, 4>::shape[i] == expected_shape[i]);
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("array elements are zero-initialized by default")
{
    GIVEN("A default-constructed 2D float array")
    {
        const std::size_t rows = 2;
        const std::size_t cols = 3;
        const bolt::array<float, 2, 3> arr;

        THEN("All elements equal zero")
        {
            for (std::size_t row = 0; row < rows; ++row)
            {
                for (std::size_t col = 0; col < cols; ++col)
                {
                    REQUIRE(arr[row, col] == 0.0F);
                }
            }
        }
    }

    GIVEN("A default-constructed 2D double array")
    {
        const std::size_t rows = 2;
        const std::size_t cols = 3;
        const bolt::array<double, 2, 3> arr;

        THEN("All elements equal zero")
        {
            for (std::size_t row = 0; row < rows; ++row)
            {
                for (std::size_t col = 0; col < cols; ++col)
                {
                    REQUIRE(arr[row, col] == 0.0);
                }
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("array linear index access reads and writes elements correctly")
{
    GIVEN("A 1D array with 3 elements")
    {
        const std::array<double, 3> expected_values = {1.0, 2.0, 3.0};

        bolt::array<double, 3> arr;

        WHEN("Values are assigned via linear index")
        {
            for (std::size_t i = 0; i < expected_values.size(); ++i)
            {
                arr[i] = expected_values[i];
            }

            THEN("The values are read back correctly via linear index")
            {
                for (std::size_t i = 0; i < expected_values.size(); ++i)
                {
                    REQUIRE(arr[i] == expected_values[i]);
                }
            }

            THEN("The values are read back correctly via a const reference")
            {
                const auto& const_arr = arr;

                for (std::size_t i = 0; i < expected_values.size(); ++i)
                {
                    REQUIRE(const_arr[i] == expected_values[i]);
                }
            }
        }
    }

    GIVEN("A 2D array with 2 rows and 3 columns")
    {
        constexpr std::array<double, 6> expected_values = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};
        bolt::array<double, 2, 3> arr;

        WHEN("Values are assigned via linear index")
        {
            for (std::size_t i = 0; i < expected_values.size(); ++i)
            {
                arr[i] = expected_values[i];
            }

            THEN("The values are read back correctly via linear index")
            {
                for (std::size_t i = 0; i < expected_values.size(); ++i)
                {
                    REQUIRE(arr[i] == expected_values[i]);
                }
            }
        }
    }

    GIVEN("A 3D array with 2x2x2 dimensions")
    {
        constexpr std::array<double, 8> expected_values = {
            {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}
        };
        bolt::array<double, 2, 2, 2> arr;

        WHEN("Values are assigned via linear index")
        {
            for (std::size_t i = 0; i < expected_values.size(); ++i)
            {
                arr[i] = expected_values[i];
            }

            THEN("The values are read back correctly via linear index")
            {
                for (std::size_t i = 0; i < expected_values.size(); ++i)
                {
                    REQUIRE(arr[i] == expected_values[i]);
                }
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("array multi-dimensional index access reads and writes elements correctly")
{
    GIVEN("A 2D array with 2 rows and 3 columns")
    {
        constexpr std::array<double, 6> expected_values = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};
        bolt::array<double, 2, 3> arr;

        WHEN("Values are assigned via multi-dimensional indices")
        {
            for (std::size_t row = 0; row < 2; ++row)
            {
                for (std::size_t col = 0; col < 3; ++col)
                {
                    arr[row, col] = expected_values[(row * 3) + col];
                }
            }

            THEN("The values are read back correctly via multi-dimensional indices")
            {
                for (std::size_t row = 0; row < 2; ++row)
                {
                    for (std::size_t col = 0; col < 3; ++col)
                    {
                        REQUIRE(arr[row, col] == expected_values[(row * 3) + col]);
                    }
                }
            }

            THEN("The values are consistent with row-major linear indexing")
            {
                for (std::size_t i = 0; i < expected_values.size(); ++i)
                {
                    REQUIRE(arr[i] == expected_values[i]);
                }
            }
        }
    }

    GIVEN("A 3D array with 2x2x2 dimensions")
    {
        constexpr std::array<double, 8> expected_values = {
            {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}
        };
        bolt::array<double, 2, 2, 2> arr;

        WHEN("Values are assigned via multi-dimensional indices")
        {
            for (std::size_t i = 0; i < 2; ++i)
            {
                for (std::size_t j = 0; j < 2; ++j)
                {
                    for (std::size_t k = 0; k < 2; ++k)
                    {
                        arr[i, j, k] = expected_values[(i * 4) + (j * 2) + k];
                    }
                }
            }

            THEN("The values are read back correctly via multi-dimensional indices")
            {
                for (std::size_t i = 0; i < 2; ++i)
                {
                    for (std::size_t j = 0; j < 2; ++j)
                    {
                        for (std::size_t k = 0; k < 2; ++k)
                        {
                            REQUIRE(arr[i, j, k] == expected_values[(i * 4) + (j * 2) + k]);
                        }
                    }
                }
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("array supports move semantics")
{
    GIVEN("A 1D array with assigned values")
    {
        const std::array<double, 2> expected_values = {1.0, 2.0};

        WHEN("The array is move-constructed")
        {
            bolt::array<double, 2> original;

            for (std::size_t i = 0; i < expected_values.size(); ++i)
            {
                original[i] = expected_values[i];
            }

            bolt::array<double, 2> moved = std::move(original);

            THEN("The moved-to array holds the original values")
            {
                for (std::size_t i = 0; i < expected_values.size(); ++i)
                {
                    REQUIRE(moved[i] == expected_values[i]);
                }
            }
        }

        WHEN("The array is move-assigned")
        {
            bolt::array<double, 2> original;
            for (std::size_t i = 0; i < expected_values.size(); ++i)
            {
                original[i] = expected_values[i];
            }

            bolt::array<double, 2> dest;
            dest = std::move(original);

            THEN("The destination array holds the original values")
            {
                for (std::size_t i = 0; i < expected_values.size(); ++i)
                {
                    REQUIRE(dest[i] == expected_values[i]);
                }
            }
        }
    }
}
