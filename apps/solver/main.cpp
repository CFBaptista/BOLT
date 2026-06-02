#include <exception>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

#include "CLI/CLI.hpp"
#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include <toml++/impl/parse_error.hpp>
#include <toml++/impl/parser.hpp>
#include <toml++/impl/table.hpp>
#include <toml++/toml.hpp>

#include "CommandLineOptions.hpp"
#include "configuration.hpp"
#include "logger.hpp"

auto main(int argc, char* argv[]) -> int
{
    CLI::App app{"BOLT (Boltzmann Operator Lattice Toolkit) is a C++ library for Computational "
                 "Fluid Dynamics based on the Lattice Boltzmann Method."};

    const CommandLineOptions options = configure_options(app);
    CLI11_PARSE(app, argc, argv);

    quill::Logger* logger = nullptr;
    try
    {
        logger = configure_logger(options.output_directory, options.log_level);
    }
    catch (const std::exception& e)
    {
        std::cerr << std::format("Failed to configure logger: {}\n", e.what());
        return 1;
    }

    toml::table configuration;
    try
    {
        LOG_INFO(logger, "Parsing configuration file");

        configuration = toml::parse_file(options.config_file.string());

        LOG_INFO(logger, "Configuration file parsed successfully");
    }
    catch (const toml::parse_error& e)
    {
        LOG_ERROR(logger, "Failed to parse configuration file:\n{}", e.what());
        return 1;
    }

    try
    {
        LOG_INFO(logger, "Validating configuration");
        validate_configuration(configuration);
    }
    catch (const std::exception& e)
    {
        LOG_ERROR(logger, "Configuration validation failed: {}", e.what());
        return 1;
    }

    return 0;
}
