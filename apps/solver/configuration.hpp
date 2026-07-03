#pragma once

#include <cstddef>
#include <filesystem>
#include <span>
#include <string>

#include <CLI/CLI.hpp>
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include <toml++/toml.hpp>

/**
 * @brief Command line options for the LBM solver.
 */
struct CommandLineOptions
{
    /** Path to the configuration file. */
    std::filesystem::path config_file;
    /** Output directory for logs and results. */
    std::filesystem::path output_directory = ".";
    /** Log level for the logger. */
    std::string log_level = "info";
};

/**
 * @brief Input and output configuration for the LBM solver.
 */
struct IOConfiguration
{
    /** Path to the configuration file. */
    std::string configuration_file;
    /** Output directory for logs and results. */
    std::string output_directory;
    /** Log level for the logger. */
    std::string log_level;
};

/**
 * @brief Time configuration for the LBM solver.
 */
struct TimeConfiguration
{
    /** Starting time for the simulation. */
    double starting_time;
    /** Time step for the simulation. */
    double time_step;
    /** Number of time steps for the simulation. */
    std::size_t number_of_steps;
};

/**
 * @brief Application configuration for the LBM solver.
 */
struct ApplicationConfiguration
{
    /** Input and output configuration. */
    IOConfiguration io{};
    /** Time configuration. */
    TimeConfiguration time{};
};

/**
 * @brief Validates the command line options for the LBM solver.
 *
 * @param options The command line options to validate.
 *
 * @throws std::invalid_argument if the options are invalid
 */
auto validate_command_line_options(const CommandLineOptions& options) -> void;

/**
 * @brief Parse command line options for the LBM solver.
 *
 * @param args Command line arguments.
 *
 * @return Parsed command line options.
 */
auto read_command_line_options(std::span<char*> args) -> CommandLineOptions;

/**
 * @brief Validates the configuration input for the LBM solver.
 *
 * @param configuration The TOML configuration table to validate.
 *
 * @throws std::invalid_argument if the configuration is invalid.
 */
auto validate_configuration_file(const toml::table& configuration) -> void;

/**
 * @brief Reads the TOML configuration file for the LBM solver.
 *
 * @param file_path Path to the TOML configuration file.
 *
 * @return Parsed TOML configuration table.
 */
auto read_configuration_file(const std::filesystem::path& file_path) -> toml::table;

/**
 * @brief Parse command-line arguments and the input configuration file for the LBM solver.

 * @param args Command line arguments.
 *
 * @return Parsed application configuration.
 */
auto parse_configuration(std::span<char*> args) -> ApplicationConfiguration;
