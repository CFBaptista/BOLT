#include <filesystem>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <CLI/CLI.hpp>
#include <catch2/catch_test_macros.hpp>

#include "bolt/solver/configuration/configuration.hpp"
#include "configuration_helper.hpp"

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

        GIVEN("A valid configuration table")
        {
            const toml::table config_table = toml::parse_file(config_filepath.string());

            WHEN("The configuration table is validated")
            {
                THEN("No exception is thrown")
                {
                    REQUIRE_NOTHROW(
                        bolt::app::detail::validate_configuration_file_settings(config_table)
                    );
                }
            }
        }
    }
}

SCENARIO("Parsing an invalid configuration setting throws an exception")
{
    GIVEN("A configuration table")
    {
        const std::filesystem::path config_filepath =
            std::filesystem::path{__FILE__}.parent_path().parent_path().parent_path() / "data" /
            "configuration.toml";

        toml::table config_table = toml::parse_file(config_filepath.string());

        GIVEN("Start time as string")
        {
            const std::string start_time = "Foo bar";

            config_table.insert_or_assign("start_time", start_time);

            WHEN("The configuration table is validated")
            {
                THEN("An exception is thrown")
                {
                    REQUIRE_THROWS_AS(
                        bolt::app::detail::validate_configuration_file_settings(config_table),
                        std::invalid_argument
                    );
                }
            }
        }

        GIVEN("Time step as string")
        {
            const std::string time_step = "Foo bar";

            config_table.insert_or_assign("time_step", time_step);

            WHEN("The configuration table is validated")
            {
                THEN("An exception is thrown")
                {
                    REQUIRE_THROWS_AS(
                        bolt::app::detail::validate_configuration_file_settings(config_table),
                        std::invalid_argument
                    );
                }
            }
        }

        GIVEN("A zero time step")
        {
            const double time_step = 0.0;

            config_table.insert_or_assign("time_step", time_step);

            WHEN("The configuration table is validated")
            {
                THEN("An exception is thrown")
                {
                    REQUIRE_THROWS_AS(
                        bolt::app::detail::validate_configuration_file_settings(config_table),
                        std::invalid_argument
                    );
                }
            }
        }

        GIVEN("A negative time step")
        {
            const double time_step = -0.1;

            config_table.insert_or_assign("time_step", time_step);

            WHEN("The configuration table is validated")
            {
                THEN("An exception is thrown")
                {
                    REQUIRE_THROWS_AS(
                        bolt::app::detail::validate_configuration_file_settings(config_table),
                        std::invalid_argument
                    );
                }
            }
        }

        GIVEN("Number of steps as string")
        {
            const std::string number_of_steps = "Foo bar";

            config_table.insert_or_assign("number_of_steps", number_of_steps);

            WHEN("The configuration table is validated")
            {
                THEN("An exception is thrown")
                {
                    REQUIRE_THROWS_AS(
                        bolt::app::detail::validate_configuration_file_settings(config_table),
                        std::invalid_argument
                    );
                }
            }
        }

        GIVEN("A zero number of steps")
        {
            const int number_of_steps = 0;

            config_table.insert_or_assign("number_of_steps", number_of_steps);

            WHEN("The configuration table is validated")
            {
                THEN("An exception is thrown")
                {
                    REQUIRE_THROWS_AS(
                        bolt::app::detail::validate_configuration_file_settings(config_table),
                        std::invalid_argument
                    );
                }
            }
        }

        GIVEN("A negative number of steps")
        {
            const int number_of_steps = -1;

            config_table.insert_or_assign("number_of_steps", number_of_steps);

            WHEN("The configuration table is validated")
            {
                THEN("An exception is thrown")
                {
                    REQUIRE_THROWS_AS(
                        bolt::app::detail::validate_configuration_file_settings(config_table),
                        std::invalid_argument
                    );
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
