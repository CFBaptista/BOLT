#include <filesystem>
#include <fstream>
#include <span>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "solver/configuration.hpp"

SCENARIO("Application configuration is constructed correctly")
{
    GIVEN("A valid configuration file")
    {
        const std::filesystem::path config_file =
            std::filesystem::temp_directory_path() / "test_config.toml";
        const std::string config_content = R"(
            start_time = 0.0
            time_step = 0.1
            number_of_steps = 10
        )";
        std::ofstream(config_file) << config_content;

        GIVEN("Only mandatory command line options are provided")
        {
            std::string program_name = "./bolt";
            std::string config_flag = "--config_file";
            std::string config_argument = config_file.string();

            std::vector<char*> argv = {
                program_name.data(), config_flag.data(), config_argument.data()
            };
            std::span<char*> args{argv};

            WHEN("The configuration file is parsed")
            {
                const ApplicationConfiguration config = parse_configuration(args);

                THEN("The configuration values are read correctly")
                {
                    REQUIRE(config.io.configuration_file == config_file.string());
                    REQUIRE(config.io.output_directory == ".");
                    REQUIRE(config.io.log_level == "info");

                    REQUIRE(config.time.start_time == 0.0);
                    REQUIRE(config.time.time_step == 0.1);
                    REQUIRE(config.time.number_of_steps == 10);
                }
            }
        }

        GIVEN("Mandatory and optional command line options are provided")
        {
            std::string program_name = "./bolt";
            std::string config_flag = "--config_file";
            std::string config_argument = config_file.string();
            std::string output_flag = "--output_directory";
            std::string output_argument = "/tmp/output";
            std::string log_level_flag = "--log_level";
            std::string log_level_argument = GENERATE(
                "trace_l3", "trace_l2", "trace_l1", "debug", "info", "notice", "warning", "error",
                "critical"
            );

            std::vector<char*> argv = {program_name.data(),      config_flag.data(),
                                       config_argument.data(),   output_flag.data(),
                                       output_argument.data(),   log_level_flag.data(),
                                       log_level_argument.data()};
            std::span<char*> args{argv};

            std::filesystem::create_directory(output_argument);

            WHEN("The configuration file is parsed")
            {
                const ApplicationConfiguration config = parse_configuration(args);

                THEN("The configuration values are read correctly")
                {
                    REQUIRE(config.io.output_directory == output_argument);
                    REQUIRE(config.io.log_level == log_level_argument);
                }
            }
        }

        std::filesystem::remove(config_file);
    }
}
