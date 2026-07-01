#pragma once

#include <filesystem>
#include <string>

#include <CLI/CLI.hpp>

/**
 * @brief Command line options for the BOLT solver
 */
struct CommandLineOptions
{
    /** Path to the configuration file */
    std::filesystem::path config_file;
    /** Output directory for logs and results */
    std::filesystem::path output_directory = ".";
    /** Log level for the logger */
    std::string log_level = "info";
};

auto configure_options(CLI::App& app, CommandLineOptions& options) -> void;
