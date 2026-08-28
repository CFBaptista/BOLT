#include <cstddef>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "bolt/config/ConfigurationManager.hpp"
#include "bolt/config/configuration_types.hpp"

namespace
{

// NOLINTNEXTLINE(cert-err58-cpp)
const std::filesystem::path TEST_CONFIGURATION_FILE{
    std::filesystem::path{BOLT_TEST_DATA_DIRECTORY} / "configuration.toml"
};

} // anonymous namespace

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("ConfigurationManager reads values from the configuration file")
{
    GIVEN("A valid configuration file")
    {
        const double expected_start_time = 0.0;
        const double expected_time_step = 0.1;
        const std::size_t expected_number_of_steps = 10;
        const std::string expected_log_level = "info";

        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{"test", "-c", config_path};
        const bolt::config::ConfigurationManager manager{args};

        THEN("The start time is read from the configuration file")
        {
            REQUIRE(manager.get_config_value<double>("start_time") == expected_start_time);
        }

        THEN("The time step is read from the configuration file")
        {
            REQUIRE(manager.get_config_value<double>("time_step") == expected_time_step);
        }

        THEN("The number of steps is read from the configuration file")
        {
            REQUIRE(
                manager.get_config_value<std::size_t>("number_of_steps") == expected_number_of_steps
            );
        }

        THEN("The log level is read from the configuration file")
        {
            REQUIRE(manager.get_config_value<std::string>("log_level") == expected_log_level);
        }
    }
}

SCENARIO("ConfigurationManager::get_config_value() throws for invalid lookups")
{
    GIVEN("A valid configuration file")
    {
        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{"test", "-c", config_path};
        const bolt::config::ConfigurationManager manager{args};

        THEN("A missing key throws an invalid_argument exception")
        {
            REQUIRE_THROWS_AS(manager.get_config_value<int>("missing_key"), std::invalid_argument);
        }

        THEN("A type mismatch throws an invalid_argument exception")
        {
            REQUIRE_THROWS_AS(manager.get_config_value<int>("log_level"), std::invalid_argument);
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("ConfigurationManager::parse() updates values from command-line arguments")
{
    GIVEN("Arguments that include a registered option value")
    {
        const std::string expected_output_directory = "/output";

        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{
            "test", "-c", config_path, "--output", expected_output_directory
        };
        bolt::config::ConfigurationManager manager{args};

        WHEN("The options are registered and parse() is called")
        {
            std::filesystem::path config_file;
            std::string output_directory;

            manager.add_cli_option("-c,--config_file", config_file, "Configuration file");
            manager.add_cli_option("--output", output_directory, "Output directory");
            manager.parse();

            THEN("The bound variable is updated with the command-line value")
            {
                REQUIRE(output_directory == expected_output_directory);
            }
        }
    }
}

SCENARIO(
    "ConfigurationManager::parse() overwrites values from the configuration file with command-line "
    "arguments"
)
{
    GIVEN("A valid configuration file and command-line arguments that override its values")
    {
        const std::string expected_log_level = "debug";

        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{"test", "-c", config_path, "--log_level", "debug"};
        bolt::config::ConfigurationManager manager{args};

        WHEN("An IOConfiguration is constructed and parse() is called")
        {
            bolt::config::IOConfiguration io_config{manager};
            manager.parse();

            THEN("The log level matches the command-line argument value")
            {
                REQUIRE(io_config.log_level == expected_log_level);
            }
        }
    }
}

SCENARIO("ConfigurationManager constructor throws for an invalid configuration file path")
{
    GIVEN("A path to a non-existent configuration file")
    {
        const std::vector<std::string_view> args{"test", "-c", "/nonexistent/config.toml"};

        THEN("A runtime_error exception is thrown")
        {
            REQUIRE_THROWS_AS(bolt::config::ConfigurationManager{args}, std::runtime_error);
        }
    }
}

SCENARIO("ConfigurationManager::parse() throws for unrecognized command-line options")
{
    GIVEN("A configuration manager with unregistered options in the arguments")
    {
        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{"test", "-c", config_path};
        bolt::config::ConfigurationManager manager{args};

        THEN("parse() throws a runtime_error exception")
        {
            REQUIRE_THROWS_AS(manager.parse(), std::runtime_error);
        }
    }
}
