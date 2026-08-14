#include <stdexcept>

#include <catch2/catch_test_macros.hpp>

#include "bolt/config/validation.hpp"

SCENARIO("NumberValidator accepts values that satisfy the requested bounds")
{
    GIVEN("A validator for a value")
    {
        const int value = 5;
        const int lower_bound = 3;
        const int upper_bound = 7;

        bolt::config::NumberValidator<int> validator{value};

        WHEN("It is checked to be greater than a smaller value")
        {
            const auto& result = validator.greater_than(lower_bound);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be greater than or equal to a smaller value")
        {
            const auto& result = validator.greater_or_equal(lower_bound);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be greater than or equal to its own value")
        {
            const auto& result = validator.greater_or_equal(value);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be less than a greater value")
        {
            const auto& result = validator.less_than(upper_bound);

            THEN("the validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be lesser than or equal to a greater value")
        {
            const auto& result = validator.less_or_equal(upper_bound);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be lesser than or equal to its own value")
        {
            const auto& result = validator.less_or_equal(value);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be between the lower and upper bounds")
        {
            const auto& result = validator.between(lower_bound, upper_bound);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }
    }
}

SCENARIO("NumberValidator rejects values that violate the requested bounds")
{
    GIVEN("A validator for a value")
    {
        const int value = 5;
        const int less_than_lower_bound = 3;
        const int less_than_upper_bound = 4;
        const int greater_than_lower_bound = 6;
        const int greater_than_upper_bound = 10;

        bolt::config::NumberValidator<int> validator{value};

        WHEN("It is checked to be greater than its own value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.greater_than(value), std::invalid_argument);
            }
        }

        WHEN("It is checked to be greater than or equal to a greater value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    validator.greater_or_equal(greater_than_lower_bound), std::invalid_argument
                );
            }
        }

        WHEN("It is checked to be less than its own value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.less_than(value), std::invalid_argument);
            }
        }

        WHEN("It is checked to be less than or equal to a smaller value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    validator.less_or_equal(less_than_upper_bound), std::invalid_argument
                );
            }
        }

        WHEN("It is checked to be between bounds that are both greater than its own value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    validator.between(greater_than_lower_bound, greater_than_upper_bound),
                    std::invalid_argument
                );
            }
        }

        WHEN("It is checked to be between bounds that are both less than its own value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    validator.between(less_than_lower_bound, less_than_upper_bound),
                    std::invalid_argument
                );
            }
        }
    }
}
