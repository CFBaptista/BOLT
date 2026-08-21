#pragma once

#include <cstddef>
#include <filesystem>
#include <memory>
#include <span>
#include <string>
#include <string_view>

// #include <CLI/CLI.hpp>
// #include <toml++/toml.hpp>

namespace CLI
{
class App;
} // namespace CLI

namespace toml
{
inline namespace v3
{

class table;

} // namespace v3

using table = v3::table;

} // namespace toml

namespace bolt::config
{

/// @brief A class to parse command-line arguments and manage settings from input files.
class ArgumentParser
{
public:
    ArgumentParser() = delete;

    /// @brief Initialize the class with command-line arguments.
    ///
    /// @param args A span of string views representing the command-line arguments.
    explicit ArgumentParser(std::span<const std::string_view> args);

    ArgumentParser(const ArgumentParser&) = delete;

    /// @brief Move constructor.
    ///
    /// @param other The other ArgumentParser instance to move from.
    ArgumentParser(ArgumentParser&& other) = default;

    auto operator=(const ArgumentParser&) -> ArgumentParser& = delete;

    /// @brief Move assignment operator.
    ///
    /// @param other The other ArgumentParser instance to move from.
    ///
    /// @return Reference to the current ArgumentParser instance.
    auto operator=(ArgumentParser&& other) -> ArgumentParser& = default;

    /// @brief Destructor.
    ~ArgumentParser();

    /// @brief Get the CLI application instance.
    ///
    /// @return Reference to the CLI application instance.
    auto get_app() -> CLI::App&;

    /// @brief Get the TOML table instance.
    ///
    /// @return Reference to the TOML table instance.
    auto get_table() -> toml::table&;

    /// @brief Parse the command-line arguments.
    auto parse() -> void;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;

    std::span<const std::string_view> args_;
};

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
    /// @param argument_parser Argument parser instance to bind options to.
    explicit IOConfiguration(ArgumentParser& argument_parser);

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
    /// @param argument_parser Argument parser instance to bind options to.
    explicit TimeConfiguration(ArgumentParser& argument_parser);

    /// @brief Validates the configuration.
    auto validate() const -> void;

private:
    auto update_from_toml_(const toml::table& table) -> void;
};

} // namespace bolt::config
