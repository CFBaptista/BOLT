#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "configuration/configuration.hpp"

SCENARIO("Reading a valid configuration file does not throw an exception")
{
    GIVEN("A valid configuration file")
    {
        const std::filesystem::path config_filepath =
            std::filesystem::path{__FILE__}.parent_path().parent_path().parent_path() / "data" /
            "configuration.toml";
        const std::string config_filepath_string = config_filepath.string();

        const std::vector<std::string_view> args{"./bolt", "--config_file", config_filepath_string};

        WHEN("The configuration is read")
        {
            THEN("No exception is thrown")
            {
                REQUIRE_NOTHROW(parse_configuration(args));
            }
        }
    }
}
