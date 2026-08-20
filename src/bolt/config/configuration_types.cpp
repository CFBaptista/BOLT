#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <iterator>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <CLI/CLI.hpp>
#include <toml++/toml.hpp>

#include "bolt/config/configuration_types.hpp"

#include "toml_parser.hpp"
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

/// @brief Parse command-line arguments.
///
/// @param app CLI application instance.
/// @param args Command-line arguments.
///
/// @throws std::invalid_argument if the command-line arguments are invalid.
/// @throws CLI::ParseError if the command-line arguments cannot be parsed.
auto parse_cli(CLI::App& app, std::span<const std::string_view> args) -> void
{
    auto argv{cli11_compatible_args_from_main(args)};
    app.parse(static_cast<int>(argv.size()), argv.data());
}

/// @brief Get the configuration file path from command-line arguments.
///
/// @param args Command-line arguments.
///
/// @return Path to the configuration file.
auto get_configuration_filepath(std::span<const std::string_view> args) -> std::filesystem::path
{
    CLI::App app{};
    std::filesystem::path configuration_filepath;

    app.add_option(
           "-c,--config_file", configuration_filepath,
           "Path to a TOML configuration file for running a simulation with BOLT"
    )
        ->required()
        ->check(CLI::ExistingFile);

    app.allow_extras();

    parse_cli(app, args);

    return configuration_filepath;
}

} // anonymous namespace

namespace bolt::config
{

struct ArgumentParser::Impl
{
    CLI::App app;
    toml::table table;
};

ArgumentParser::ArgumentParser(std::span<const std::string_view> args)
    : pimpl_{std::make_unique<Impl>()}, args_{args}
{
    const std::filesystem::path configuration_filepath{get_configuration_filepath(args)};
    pimpl_->table = toml::parse_file(configuration_filepath.string());
}

ArgumentParser::~ArgumentParser() = default;

auto ArgumentParser::parse() -> void
{
    parse_cli(pimpl_->app, args_);
}

auto ArgumentParser::get_app() -> CLI::App&
{
    return pimpl_->app;
}

auto ArgumentParser::get_table() -> toml::table&
{
    return pimpl_->table;
}

IOConfiguration::IOConfiguration(ArgumentParser& argument_parser)
    : configuration_file(""), output_directory(".")
{
    update_from_toml_(argument_parser.get_table());
    bind_to_cli_(argument_parser.get_app());
}

auto IOConfiguration::update_from_toml_(const toml::table& table) -> void
{
    log_level = get_toml_value<std::string>(table, "log_level");
}

auto IOConfiguration::bind_to_cli_(CLI::App& app) -> void
{
    app.add_option(
           "-c,--config_file", configuration_file,
           "Path to a TOML configuration file for running a simulation with BOLT"
    )
        ->required()
        ->check(CLI::ExistingFile);

    app.add_option(
           "-o,--output_directory", output_directory,
           "Path to the output directory for logs and simulation results"
    )
        ->default_str(output_directory)
        ->check(CLI::ExistingDirectory);

    app.add_option(
           "-l,--log_level", log_level, "Logging level (trace, debug, info, warning, error)"
    )
        ->default_str(log_level)
        ->check(CLI::IsMember({"trace", "debug", "info", "warning", "error"}));
}

auto IOConfiguration::validate() const -> void
{
    DirectoryValidator(output_directory).exists().is_directory().readable().writable();

    FileValidator(configuration_file).exists().is_file().readable();

    if (log_level != "trace" && log_level != "debug" && log_level != "info" &&
        log_level != "warning" && log_level != "error")
    {
        throw std::invalid_argument("Invalid log level: " + log_level);
    }
}

TimeConfiguration::TimeConfiguration(ArgumentParser& argument_parser)
    : start_time(-1.0), time_step(0.0), number_of_steps(0)
{
    update_from_toml_(argument_parser.get_table());
}

auto TimeConfiguration::update_from_toml_(const toml::table& table) -> void
{
    start_time = get_toml_value<double>(table, "start_time");
    time_step = get_toml_value<double>(table, "time_step");
    number_of_steps = get_toml_value<std::size_t>(table, "number_of_steps");
}

auto TimeConfiguration::validate() const -> void
{
    NumberValidator<double>(start_time).greater_or_equal(0.0);
    NumberValidator<double>(time_step).greater_than(0.0);
    NumberValidator<std::size_t>(number_of_steps).greater_than(0);
}

} // namespace bolt::config
