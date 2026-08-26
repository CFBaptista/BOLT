#include <cstddef>
#include <cstdint>
#include <limits>
#include <new>

#include <catch2/catch_test_macros.hpp>

#include "bolt/core/aligned_allocator.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("aligned_allocator allocates memory aligned to the specified boundary")
{
    GIVEN("An allocator with 64-byte alignment for double")
    {
        constexpr std::size_t alignment = 64;

        WHEN("Memory is allocated for a single element")
        {
            double* ptr = bolt::aligned_allocator<double, alignment>::allocate(1);

            THEN("The returned pointer is aligned to 64 bytes")
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
                REQUIRE(reinterpret_cast<std::uintptr_t>(ptr) % alignment == 0);
            }

            bolt::aligned_allocator<double, alignment>::deallocate(ptr, 1);
        }

        WHEN("Memory is allocated for multiple elements")
        {
            const std::size_t count = 10;
            double* ptr = bolt::aligned_allocator<double, alignment>::allocate(count);

            THEN("The returned pointer is aligned to 64 bytes")
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
                REQUIRE(reinterpret_cast<std::uintptr_t>(ptr) % alignment == 0);
            }

            bolt::aligned_allocator<double, alignment>::deallocate(ptr, count);
        }
    }

    GIVEN("An allocator with 32-byte alignment for float")
    {
        constexpr std::size_t alignment = 32;

        WHEN("Memory is allocated for a single element")
        {
            float* ptr = bolt::aligned_allocator<float, alignment>::allocate(1);

            THEN("The returned pointer is aligned to 32 bytes")
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
                REQUIRE(reinterpret_cast<std::uintptr_t>(ptr) % alignment == 0);
            }

            bolt::aligned_allocator<float, alignment>::deallocate(ptr, 1);
        }
    }
}

SCENARIO("aligned_allocator throws on element count overflow")
{
    GIVEN("An allocator for double")
    {
        constexpr std::size_t alignment = 64;

        THEN("Allocating more elements than std::size_t can hold throws bad_array_new_length")
        {
            const std::size_t overflow_count =
                (std::numeric_limits<std::size_t>::max() / sizeof(double)) + 1;

            REQUIRE_THROWS_AS(
                (bolt::aligned_allocator<double, alignment>::allocate(overflow_count)),
                std::bad_array_new_length
            );
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("aligned_allocator equality comparison")
{
    GIVEN("Two allocators of different types with the same alignment")
    {
        const bolt::aligned_allocator<double, 64> left;
        const bolt::aligned_allocator<float, 64> right;

        THEN("They compare as equal")
        {
            REQUIRE(left == right);
        }
    }

    GIVEN("Two allocators of the same type with different alignments")
    {
        const bolt::aligned_allocator<double, 64> left;
        const bolt::aligned_allocator<double, 32> right;

        THEN("They compare as not equal")
        {
            REQUIRE_FALSE(left == right);
        }
    }
}
