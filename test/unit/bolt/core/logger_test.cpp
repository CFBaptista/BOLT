#include <filesystem>
#include <stdexcept>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "bolt/core/logger.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("create_logger returns a valid logger for supported log levels")
{
    GIVEN("A temporary output directory")
    {
        const std::filesystem::path output_directory = std::filesystem::temp_directory_path();

        THEN("No exception is thrown for the 'trace' log level")
        {
            REQUIRE_NOTHROW(bolt::core::create_logger(output_directory, "trace"));
        }

        THEN("No exception is thrown for the 'debug' log level")
        {
            REQUIRE_NOTHROW(bolt::core::create_logger(output_directory, "debug"));
        }

        THEN("No exception is thrown for the 'info' log level")
        {
            REQUIRE_NOTHROW(bolt::core::create_logger(output_directory, "info"));
        }

        THEN("No exception is thrown for the 'warning' log level")
        {
            REQUIRE_NOTHROW(bolt::core::create_logger(output_directory, "warning"));
        }

        THEN("No exception is thrown for the 'error' log level")
        {
            REQUIRE_NOTHROW(bolt::core::create_logger(output_directory, "error"));
        }
    }
}

SCENARIO("create_logger throws for an unrecognized log level")
{
    GIVEN("A temporary output directory")
    {
        const std::filesystem::path output_directory = std::filesystem::temp_directory_path();

        THEN("An invalid_argument exception is thrown for an unrecognized log level")
        {
            REQUIRE_THROWS_AS(
                bolt::core::create_logger(output_directory, "verbose"), std::invalid_argument
            );
        }
    }
}
