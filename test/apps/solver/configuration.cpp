#include <array>
#include <filesystem>
#include <fstream>
#include <span>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "solver/configuration.hpp"

SCENARIO("Configuration file is read correctly")
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

        std::string program_name = "./bolt";
        std::string config_flag = "--config_file";
        std::string config_argument = config_file.string();
        std::array<char*, 3> argv = {
            program_name.data(), config_flag.data(), config_argument.data()
        };
        std::span<char*> args{argv};

        WHEN("The configuration file is parsed")
        {
            const ApplicationConfiguration config = parse_configuration(args);

            THEN("The configuration values are read correctly")
            {
                REQUIRE(config.io.configuration_file == config_file.string());
                REQUIRE(config.time.start_time == 0.0);
                REQUIRE(config.time.time_step == 0.1);
                REQUIRE(config.time.number_of_steps == 10);
            }
        }

        std::filesystem::remove(config_file);
    }
}
