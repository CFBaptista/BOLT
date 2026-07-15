#pragma once

#include <filesystem>
#include <span>
#include <string_view>

#include <CLI/CLI.hpp>
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include <toml++/toml.hpp>

#include "configuration_datatypes.hpp"

/**
 * @brief Parse command line options for the LBM solver.
 *
 * @param args Command line arguments.
 *
 * @return Parsed command line options.
 */
auto read_command_line_options(std::span<const std::string_view> args) -> CommandLineOptions;

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
auto parse_configuration(std::span<const std::string_view> args) -> ApplicationConfiguration;
