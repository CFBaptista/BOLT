#include <format>
#include <stdexcept>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <toml++/toml.hpp>

#include "bolt/config/toml_parser.hpp"

SCENARIO("Retrieve values from a table")
{
    GIVEN("A TOML table with supported values")
    {
        const int value = 42;
        const double volume = 3.14;
        const float temperature = -273.15F;
        const std::string name = "Alice";
        const bool enabled = true;
        const double tolerance = 1e-6;

        const auto table = toml::parse(
            std::format(
                R"(
                        answer = {}
                        volume = {}
                        temperature = {}
                        name = "{}"
                        enabled = {}
                    )",
                value, volume, temperature, name, enabled
            )
        );

        THEN("The requested value is returned with the expected type")
        {
            REQUIRE(bolt::config::get_toml_value<int>(table, "answer") == value);
            REQUIRE_THAT(
                bolt::config::get_toml_value<float>(table, "answer"),
                Catch::Matchers::WithinRel(value, tolerance)
            );
            REQUIRE_THAT(
                bolt::config::get_toml_value<double>(table, "answer"),
                Catch::Matchers::WithinRel(value, tolerance)
            );

            REQUIRE_THAT(
                bolt::config::get_toml_value<float>(table, "volume"),
                Catch::Matchers::WithinRel(volume, tolerance)
            );
            REQUIRE_THAT(
                bolt::config::get_toml_value<double>(table, "volume"),
                Catch::Matchers::WithinRel(volume, tolerance)
            );

            REQUIRE_THAT(
                bolt::config::get_toml_value<float>(table, "temperature"),
                Catch::Matchers::WithinRel(
                    static_cast<float>(temperature), static_cast<float>(tolerance)
                )
            );
            REQUIRE_THAT(
                bolt::config::get_toml_value<double>(table, "temperature"),
                Catch::Matchers::WithinRel(static_cast<double>(temperature), tolerance)
            );

            REQUIRE(bolt::config::get_toml_value<std::string>(table, "name") == name);

            REQUIRE(bolt::config::get_toml_value<bool>(table, "enabled") == enabled);
        }
    }
}

SCENARIO("Invalid lookups throw exceptions")
{
    GIVEN("A TOML table without the requested key")
    {
        const toml::table table;

        THEN("An exception is thrown for a missing key")
        {
            REQUIRE_THROWS_AS(
                bolt::config::get_toml_value<int>(table, "answer"), std::invalid_argument
            );
        }
    }

    GIVEN("A TOML table with a value that cannot be converted to the requested type")
    {
        const auto table = toml::parse(R"(
            name = "Alice"
        )");

        THEN("An exception is thrown for a type mismatch")
        {
            REQUIRE_THROWS_AS(
                bolt::config::get_toml_value<int>(table, "name"), std::invalid_argument
            );
        }
    }
}
