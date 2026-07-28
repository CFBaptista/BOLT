#include <chrono>
#include <format>
#include <regex>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "bolt/core/timestamp.hpp"

SCENARIO("Timestamp adheres to ISO 8601")
{

    WHEN("A timestamp is generated")
    {
        const auto timestamp = bolt::core::get_timestamp();
        const std::regex pattern{R"(^\d{8}T\d{6}Z$)"};

        THEN("It is non-empty and matches the expected timestamp format")
        {
            REQUIRE_FALSE(timestamp.empty());
            REQUIRE(std::regex_match(timestamp, pattern));
        }
    }
}
