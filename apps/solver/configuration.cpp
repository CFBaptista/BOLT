#include <algorithm>
#include <array>
#include <cstddef>
#include <filesystem>
#include <format>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>

#include <CLI/CLI.hpp>
#include <toml++/toml.hpp>

#include "configuration.hpp"
#include "utilities.hpp"

auto validate_command_line_options(const CommandLineOptions& options) -> void
{
    if (!std::filesystem::exists(options.config_file))
    {
        throw std::invalid_argument(
            std::format("Configuration file does not exist: {}", options.config_file.string())
        );
    }

    if (!std::filesystem::is_regular_file(options.config_file))
    {
        throw std::invalid_argument(
            std::format(
                "Configuration file is not a regular file: {}", options.config_file.string()
            )
        );
    }

    if (!std::filesystem::exists(options.output_directory))
    {
        throw std::invalid_argument(
            std::format("Output directory does not exist: {}", options.output_directory.string())
        );
    }

    if (!std::filesystem::is_directory(options.output_directory))
    {
        throw std::invalid_argument(
            std::format(
                "Output directory is not a directory: {}", options.output_directory.string()
            )
        );
    }

    const std::array<std::string, 9> valid_log_levels = {"trace_l3", "trace_l2", "trace_l1",
                                                         "debug",    "info",     "notice",
                                                         "warning",  "error",    "critical"};
    if (std::ranges::find(valid_log_levels, options.log_level) == valid_log_levels.end())
    {
        throw std::invalid_argument(std::format("Invalid log level: {}.", options.log_level));
    }
}

auto read_command_line_options(std::span<char*> args) -> CommandLineOptions
{
    CLI::App app{};
    CommandLineOptions options;

    app.add_option(
           "-c,--config_file", options.config_file,
           "Path to a TOML configuration file for running a simulation with BOLT"
    )
        ->required();

    app.add_option(
           "-o,--output_directory", options.output_directory,
           "Path to the output directory for logs and simulation results"
    )
        ->default_str(options.output_directory);

    app.add_option(
           "-l,--log_level", options.log_level,
           "Logging level (trace, debug, info, warning, error, critical)"
    )
        ->default_str(options.log_level);

    app.parse(static_cast<int>(args.size()), args.data());

    validate_command_line_options(options);

    return options;
}

auto validate_configuration_file(const toml::table& configuration) -> void
{
    if (!configuration.contains("start_time"))
    {
        throw std::invalid_argument("Configuration file is missing required key: 'start_time'");
    }
    if (!configuration["start_time"].is_floating_point())
    {
        throw std::invalid_argument(
            "Configuration file key 'start_time' must be a floating point number"
        );
    }

    if (!configuration.contains("time_step"))
    {
        throw std::invalid_argument("Configuration file is missing required key: 'time_step'");
    }
    if (!configuration["time_step"].is_floating_point())
    {
        throw std::invalid_argument(
            "Configuration file key 'time_step' must be a floating point number"
        );
    }
    if (configuration["time_step"].value<double>() <= 0.0)
    {
        throw std::invalid_argument(
            "Configuration file key 'time_step' must be a positive definite floating point number"
        );
    }

    if (!configuration.contains("number_of_steps"))
    {
        throw std::invalid_argument(
            "Configuration file is missing required key: 'number_of_steps'"
        );
    }
    if (!configuration["number_of_steps"].is_integer())
    {
        throw std::invalid_argument("Configuration file key 'number_of_steps' must be an integer");
    }
    if (configuration["number_of_steps"].value<std::size_t>() < 1)
    {
        throw std::invalid_argument(
            "Configuration file key 'number_of_steps' must be a positive integer"
        );
    }
}

auto read_configuration_file(const std::filesystem::path& file_path) -> toml::table
{
    toml::table configuration;
    try
    {
        configuration = toml::parse_file(file_path.string());
    }
    catch (const toml::parse_error& e)
    {
        std::cerr << std::format("Failed to parse configuration file: {}", e.what());
        throw;
    }

    validate_configuration_file(configuration);

    return configuration;
}

auto parse_configuration(std::span<char*> args) -> ApplicationConfiguration
{
    const CommandLineOptions options = read_command_line_options(args);
    const toml::table configuration = read_configuration_file(options.config_file);

    const auto start_time = get_toml_value<double>(configuration, "start_time");
    const auto time_step = get_toml_value<double>(configuration, "time_step");
    const auto number_of_steps = get_toml_value<std::size_t>(configuration, "number_of_steps");

    const IOConfiguration io_configuration{
        .configuration_file = options.config_file.string(),
        .output_directory = options.output_directory.string(),
        .log_level = options.log_level,
    };

    const TimeConfiguration time_configuration{
        .start_time = start_time,
        .time_step = time_step,
        .number_of_steps = number_of_steps,
    };

    const ApplicationConfiguration application_configuration{
        .io = io_configuration,
        .time = time_configuration,
    };

    return application_configuration;
}
