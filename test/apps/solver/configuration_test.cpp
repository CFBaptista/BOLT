#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include <CLI/CLI.hpp>
#include <catch2/catch_test_macros.hpp>

#include "bolt/solver/configuration.hpp"

SCENARIO("Parsing a valid configuration does not throw an exception")
{
    GIVEN("A valid configuration file")
    {
        const std::filesystem::path config_filepath =
            std::filesystem::path{__FILE__}.parent_path().parent_path().parent_path() / "data" /
            "configuration.toml";

        GIVEN("Valid command-line arguments")
        {
            const std::string config_filepath_string = config_filepath.string();

            const std::vector<std::string_view> args{
                "./bolt", "--config_file", config_filepath_string
            };

            WHEN("The configuration file is parsed")
            {
                THEN("No exception is thrown")
                {
                    REQUIRE_NOTHROW(bolt::app::parse_configuration(args));
                }
            }
        }
    }
}

SCENARIO("Parsing invalid command-line arguments throws an exception")
{
    GIVEN("Missing config file option")
    {
        const std::vector<std::string_view> args{"./bolt"};

        WHEN("The command-line arguments are parsed")
        {
            THEN("An exception is thrown")
            {
                REQUIRE_THROWS_AS(bolt::app::parse_configuration(args), CLI::ParseError);
            }
        }
    }

    GIVEN("Non-existent configuration file path")
    {
        const std::vector<std::string_view> args{
            "./bolt", "--config_file", "non_existent_config.toml"
        };

        WHEN("The command-line arguments are parsed")
        {
            THEN("An exception is thrown")
            {
                REQUIRE_THROWS_AS(bolt::app::parse_configuration(args), CLI::ParseError);
            }
        }
    }

    GIVEN("Non-existent output directory path")
    {
        const std::filesystem::path config_filepath =
            std::filesystem::path{__FILE__}.parent_path().parent_path().parent_path() / "data" /
            "configuration.toml";

        const std::string config_filepath_string = config_filepath.string();

        const std::vector<std::string_view> args{
            "./bolt", "--config_file", config_filepath_string, "--output_directory", "foo/bar"
        };

        WHEN("The command-line arguments are parsed")
        {
            THEN("An exception is thrown")
            {
                REQUIRE_THROWS_AS(bolt::app::parse_configuration(args), CLI::ParseError);
            }
        }
    }

    GIVEN("Invalid log level")
    {
        const std::filesystem::path config_filepath =
            std::filesystem::path{__FILE__}.parent_path().parent_path().parent_path() / "data" /
            "configuration.toml";

        const std::string config_filepath_string = config_filepath.string();

        const std::vector<std::string_view> args{
            "./bolt", "--config_file", config_filepath_string, "--log_level", "foobar"
        };

        WHEN("The command-line arguments are parsed")
        {
            THEN("An exception is thrown")
            {
                REQUIRE_THROWS_AS(bolt::app::parse_configuration(args), CLI::ParseError);
            }
        }
    }
}
