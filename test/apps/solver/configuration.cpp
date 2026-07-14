#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include "configuration/configuration.hpp"

SCENARIO("Reading a valid configuration file does not throw an exception")
{
    GIVEN("A valid configuration file")
    {
        const std::filesystem::path config_file =
            std::filesystem::path{__FILE__}.parent_path().parent_path().parent_path() / "data" /
            "configuration.toml";

        WHEN("The configuration is read")
        {
            THEN("No exception is thrown")
            {
                REQUIRE_NOTHROW(read_configuration_file(config_file));
            }
        }
    }
}
