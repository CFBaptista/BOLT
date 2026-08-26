#include <algorithm>
#include <filesystem>
#include <iterator>
#include <memory>
#include <span>
#include <string_view>
#include <vector>

#include <CLI/CLI.hpp>
#include <toml++/toml.hpp>

#include "toml_parser.hpp"

#include "bolt/config/ConfigurationManager.hpp"

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
    );

    app.allow_extras();

    parse_cli(app, args);

    return configuration_filepath;
}

} // anonymous namespace

namespace bolt::config
{

struct ConfigurationManager::Impl
{
    CLI::App app;
    toml::table table;
};

ConfigurationManager::ConfigurationManager(std::span<const std::string_view> args)
    : pimpl_{std::make_unique<Impl>()}, args_{args}
{
    const std::filesystem::path configuration_filepath{get_configuration_filepath(args)};
    pimpl_->table = toml::parse_file(configuration_filepath.string());
}

ConfigurationManager::~ConfigurationManager() = default;

template <typename T>
auto ConfigurationManager::add_cli_option(
    const std::string& option,
    T& value,
    const std::string& description
) -> void
{
    pimpl_->app.add_option(option, value, description);
}

template auto ConfigurationManager::add_cli_option(
    const std::string& option,
    int& value,
    const std::string& description
) -> void;
template auto ConfigurationManager::add_cli_option(
    const std::string& option,
    std::size_t& value,
    const std::string& description
) -> void;
template auto ConfigurationManager::add_cli_option(
    const std::string& option,
    double& value,
    const std::string& description
) -> void;
template auto ConfigurationManager::add_cli_option(
    const std::string& option,
    float& value,
    const std::string& description
) -> void;
template auto ConfigurationManager::add_cli_option(
    const std::string& option,
    std::string& value,
    const std::string& description
) -> void;
template auto ConfigurationManager::add_cli_option(
    const std::string& option,
    std::filesystem::path& value,
    const std::string& description
) -> void;

template <typename T>
auto ConfigurationManager::get_config_value(const std::string& key) const -> T
{
    return get_toml_value<T>(pimpl_->table, key);
}

template auto ConfigurationManager::get_config_value<int>(const std::string& key) const -> int;
template auto ConfigurationManager::get_config_value<std::size_t>(const std::string& key) const
    -> std::size_t;
template auto ConfigurationManager::get_config_value<double>(const std::string& key) const
    -> double;
template auto ConfigurationManager::get_config_value<float>(const std::string& key) const -> float;
template auto ConfigurationManager::get_config_value<std::string>(const std::string& key) const
    -> std::string;

auto ConfigurationManager::parse() -> void
{
    parse_cli(pimpl_->app, args_);
}

} // namespace bolt::config
