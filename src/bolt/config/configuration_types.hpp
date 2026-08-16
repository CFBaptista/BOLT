#pragma once

#include <cstddef>
#include <filesystem>
#include <span>
#include <string>
#include <string_view>

#include <CLI/CLI.hpp>
#include <toml++/toml.hpp>

namespace bolt::config
{

/// @brief Input and output sub-configuration for the LBM application.
class IOConfiguration
{
public:
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)

    /// @brief Path to the configuration file.
    std::filesystem::path configuration_file;
    /// @brief Output directory for logs and results.
    std::filesystem::path output_directory;
    /// @brief Log level for the logger.
    std::string log_level;

    // NOLINTEND(misc-non-private-member-variables-in-classes)

    IOConfiguration() = delete;

    /// @brief Initialize the class from a TOML table and bind to CLI options.
    ///
    /// @param table TOML table containing the configuration.
    /// @param app CLI application instance to bind options to.
    IOConfiguration(const toml::table& table, CLI::App& app);

    /// @brief Validates the configuration.
    auto validate() const -> void;

private:
    auto update_from_toml_(const toml::table& table) -> void;
    auto bind_to_cli_(CLI::App& app) -> void;
};

/// @brief Time sub-configuration for the LBM application.
class TimeConfiguration
{
public:
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)

    /// @brief Starting time for the simulation.
    double start_time;
    /// @brief Time step for the simulation.
    double time_step;
    /// @brief Number of time steps for the simulation.
    std::size_t number_of_steps;

    // NOLINTEND(misc-non-private-member-variables-in-classes)

    /// @brief Initialize the class from a TOML table and bind to CLI options.
    ///
    /// @param table TOML table containing the configuration.
    /// @param app CLI application instance to bind options to.
    TimeConfiguration(const toml::table& table, CLI::App& app);

    /// @brief Validates the configuration.
    auto validate() const -> void;

private:
    auto update_from_toml_(const toml::table& table) -> void;
};

/// @brief Get the configuration file path from command-line arguments.
///
/// @param args Command-line arguments.
///
/// @return Path to the configuration file.
auto get_configuration_filepath(std::span<const std::string_view> args) -> std::filesystem::path;

/// @brief Parse command-line arguments.
///
/// @param app CLI application instance.
/// @param args Command-line arguments.
///
/// @throws std::invalid_argument if the command-line arguments are invalid.
/// @throws CLI::ParseError if the command-line arguments cannot be parsed.
auto parse_cli(CLI::App& app, std::span<const std::string_view> args) -> void;

} // namespace bolt::config
