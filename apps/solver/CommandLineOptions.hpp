#pragma once

#include <filesystem>
#include <string>

#include "CLI/CLI.hpp"

struct CommandLineOptions
{
    std::filesystem::path config_file;
    std::filesystem::path output_directory = ".";
    std::string log_level = "info";
};

auto configure_options(CLI::App& app) -> CommandLineOptions;
