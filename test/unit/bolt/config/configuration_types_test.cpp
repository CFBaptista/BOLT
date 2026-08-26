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

// NOLINTNEXTLINE(cert-err58-cpp)
const std::filesystem::path TEST_DATA_DIRECTORY{BOLT_TEST_DATA_DIRECTORY};

} // anonymous namespace

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("TimeConfiguration reads values from the configuration file")
{
    GIVEN("A valid configuration file")
    {
        const double expected_start_time = 0.0;
        const double expected_time_step = 0.1;
        const std::size_t expected_number_of_steps = 10;

        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{"test", "-c", config_path};
        const bolt::config::ConfigurationManager manager{args};

        WHEN("A TimeConfiguration is constructed")
        {
            const bolt::config::TimeConfiguration time_config{manager};

            THEN("The start time matches the value in the configuration file")
            {
                REQUIRE(time_config.start_time == expected_start_time);
            }

            THEN("The time step matches the value in the configuration file")
            {
                REQUIRE(time_config.time_step == expected_time_step);
            }

            THEN("The number of steps matches the value in the configuration file")
            {
                REQUIRE(time_config.number_of_steps == expected_number_of_steps);
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("TimeConfiguration::validate() accepts and rejects configurations")
{
    GIVEN("A TimeConfiguration constructed from a valid configuration file")
    {
        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{"test", "-c", config_path};
        const bolt::config::ConfigurationManager manager{args};
        bolt::config::TimeConfiguration time_config{manager};

        WHEN("All field values are valid")
        {
            THEN("No exception is thrown")
            {
                REQUIRE_NOTHROW(time_config.validate());
            }
        }

        WHEN("The start time is negative")
        {
            const double negative_start_time = -1.0;
            time_config.start_time = negative_start_time;

            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(time_config.validate(), std::invalid_argument);
            }
        }

        WHEN("The time step is zero")
        {
            time_config.time_step = 0.0;

            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(time_config.validate(), std::invalid_argument);
            }
        }

        WHEN("The time step is negative")
        {
            const double negative_time_step = -0.1;
            time_config.time_step = negative_time_step;

            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(time_config.validate(), std::invalid_argument);
            }
        }

        WHEN("The number of steps is zero")
        {
            time_config.number_of_steps = 0;

            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(time_config.validate(), std::invalid_argument);
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("IOConfiguration reads values from the configuration file")
{
    GIVEN("A valid configuration file")
    {
        const std::string expected_log_level = "info";

        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{"test", "-c", config_path};
        bolt::config::ConfigurationManager manager{args};

        WHEN("An IOConfiguration is constructed")
        {
            const bolt::config::IOConfiguration io_config{manager};

            THEN("The log level matches the value in the configuration file")
            {
                REQUIRE(io_config.log_level == expected_log_level);
            }

            THEN("The configuration file path is empty by default")
            {
                REQUIRE(io_config.configuration_file.empty());
            }

            THEN("The output directory defaults to the current directory")
            {
                REQUIRE(io_config.output_directory == std::filesystem::path{"."});
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("IOConfiguration::validate() accepts and rejects configurations")
{
    GIVEN("An IOConfiguration constructed from a valid configuration file")
    {
        const std::string config_path{TEST_CONFIGURATION_FILE.string()};
        const std::vector<std::string_view> args{"test", "-c", config_path};
        bolt::config::ConfigurationManager manager{args};
        bolt::config::IOConfiguration io_config{manager};

        WHEN("All field values are valid")
        {
            io_config.output_directory = TEST_DATA_DIRECTORY;
            io_config.configuration_file = TEST_CONFIGURATION_FILE;

            THEN("No exception is thrown")
            {
                REQUIRE_NOTHROW(io_config.validate());
            }
        }

        WHEN("The log level is not one of the accepted values")
        {
            io_config.output_directory = TEST_DATA_DIRECTORY;
            io_config.configuration_file = TEST_CONFIGURATION_FILE;
            io_config.log_level = "verbose";

            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(io_config.validate(), std::invalid_argument);
            }
        }

        WHEN("The output directory does not exist")
        {
            io_config.output_directory = "/nonexistent/directory";
            io_config.configuration_file = TEST_CONFIGURATION_FILE;

            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(io_config.validate(), std::filesystem::filesystem_error);
            }
        }

        WHEN("The configuration file path is empty")
        {
            io_config.output_directory = TEST_DATA_DIRECTORY;
            io_config.configuration_file = "";

            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(io_config.validate(), std::invalid_argument);
            }
        }

        WHEN("The configuration file does not exist")
        {
            io_config.output_directory = TEST_DATA_DIRECTORY;
            io_config.configuration_file = "/nonexistent/file.toml";

            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(io_config.validate(), std::filesystem::filesystem_error);
            }
        }
    }
}
