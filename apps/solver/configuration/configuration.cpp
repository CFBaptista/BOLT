#include <cstddef>
#include <filesystem>
#include <format>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <CLI/CLI.hpp>
#include <toml++/toml.hpp>

#include "configuration.hpp"
#include "configuration_datatypes.hpp"
#include "validation.hpp"

namespace
{

auto cli11_compatible_args(std::span<const std::string_view> args) -> std::vector<char*>
{
    std::vector<char*> argv;
    argv.reserve(args.size());

    for (const auto& arg : args)
    {
        argv.push_back(
            const_cast<char*>(arg.data()) // NOLINT(cppcoreguidelines-pro-type-const-cast)
        );
    }

    return argv;
}

} // namespace

auto read_command_line_options(std::span<const std::string_view> args) -> CommandLineOptions
{
    CLI::App app{};
    CommandLineOptions options;

    app.add_option(
           "-c,--config_file", options.config_file,
           "Path to a TOML configuration file for running a simulation with BOLT"
    )
        ->required()
        ->check(CLI::ExistingFile);

    app.add_option(
           "-o,--output_directory", options.output_directory,
           "Path to the output directory for logs and simulation results"
    )
        ->default_str(options.output_directory)
        ->check(CLI::ExistingDirectory);

    app.add_option(
           "-l,--log_level", options.log_level,
           "Logging level (trace, debug, info, warning, error, critical)"
    )
        ->default_str(options.log_level)
        ->check(
            CLI::IsMember(
                {"trace_l3", "trace_l2", "trace_l1", "debug", "info", "notice", "warning", "error",
                 "critical"}
            )
        );

    auto argv{cli11_compatible_args(args)};

    app.parse(static_cast<int>(argv.size()), argv.data());

    return options;
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

    return configuration;
}

auto parse_configuration(std::span<const std::string_view> args) -> ApplicationConfiguration
{
    const CommandLineOptions options = read_command_line_options(args);
    const toml::table configuration = read_configuration_file(options.config_file);

    const auto start_time =
        NumberValidator<double>(configuration, "start_time").greater_or_equal(0.0).value();
    const auto time_step =
        NumberValidator<double>(configuration, "time_step").greater_than(0.0).value();
    const auto number_of_steps =
        NumberValidator<std::size_t>(configuration, "number_of_steps").greater_than(0).value();

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
