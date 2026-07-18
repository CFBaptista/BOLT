#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <format>
#include <iostream>
#include <iterator>
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

/// @brief Converts a span of string views into a vector of C-style string arguments compatible with
/// CLI11.
///
/// Modern C++ codebases often pack command-line arguments in a C++ container instead of propagating
/// the traditional C-style `int argc` and `char* argv[]` arguments. However, CLI11 expects C-style
/// arguments. This function converts the C++ container to a C-style array of char pointers,
/// ensuring compatibility with CLI11's parsing functions.
///
/// @param args A span of string views representing command-line arguments.
///
/// @return A vector of C-style char pointer arguments suitable for CLI11.
auto cli11_compatible_args_from_main(std::span<const std::string_view> args)
    -> std::vector<const char*>
{
    std::vector<const char*> argv;
    argv.reserve(args.size());

    std::ranges::transform(
        args, std::back_inserter(argv),
        [](const std::string_view& arg) -> const char* { return arg.data(); }
    );

    return argv;
}

} // anonymous namespace

namespace detail
{

/// @brief Parse and validate command-line options for the LBM solver.
///
/// @param args command-line arguments.
///
/// @return Validated command-line options.
// NOLINTNEXTLINE(misc-use-internal-linkage)
auto parse_command_line_options(std::span<const std::string_view> args) -> CommandLineOptions
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

    auto argv{cli11_compatible_args_from_main(args)};

    app.parse(static_cast<int>(argv.size()), argv.data());

    return options;
}

/// @brief Validate the TOML table for the LBM solver.
///
/// @param table TOML table containing configuration settings.
///
/// @return Validated configuration settings.
// NOLINTNEXTLINE(misc-use-internal-linkage)
auto validate_configuration_file_settings(const toml::table& table) -> ConfigurationFileSettings
{
    const auto start_time =
        NumberValidator<double>(table, "start_time").greater_or_equal(0.0).value();
    const auto time_step = NumberValidator<double>(table, "time_step").greater_than(0.0).value();
    const auto number_of_steps =
        NumberValidator<std::size_t>(table, "number_of_steps").greater_than(0).value();

    const ConfigurationFileSettings settings{
        .start_time = start_time,
        .time_step = time_step,
        .number_of_steps = number_of_steps,
    };

    return settings;
}

/// @brief Parse and validate the TOML configuration file for the LBM solver.
///
/// @param file_path Path to the TOML configuration file.
///
/// @return Validated configuration file settings.
// NOLINTNEXTLINE(misc-use-internal-linkage)
auto parse_configuration_file_settings(const std::filesystem::path& file_path)
    -> ConfigurationFileSettings
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

    const ConfigurationFileSettings settings = validate_configuration_file_settings(configuration);

    return settings;
}

} // namespace detail

auto parse_configuration(std::span<const std::string_view> args) -> ApplicationConfiguration
{
    const CommandLineOptions options = detail::parse_command_line_options(args);
    const ConfigurationFileSettings settings =
        detail::parse_configuration_file_settings(options.config_file);

    const IOConfiguration io_configuration{
        .configuration_file = options.config_file.string(),
        .output_directory = options.output_directory.string(),
        .log_level = options.log_level,
    };

    const TimeConfiguration time_configuration{
        .start_time = settings.start_time,
        .time_step = settings.time_step,
        .number_of_steps = settings.number_of_steps,
    };

    const ApplicationConfiguration application_configuration{
        .io = io_configuration,
        .time = time_configuration,
    };

    return application_configuration;
}
