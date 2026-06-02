#include <chrono>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "CLI/CLI.hpp"
#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include "quill/core/Common.h"
#include "quill/core/LogLevel.h"
#include "quill/core/PatternFormatterOptions.h"
#include "quill/sinks/ConsoleSink.h"
#include "quill/sinks/FileSink.h"
#include <toml++/impl/parse_error.hpp>
#include <toml++/impl/parser.hpp>
#include <toml++/impl/table.hpp>
#include <toml++/toml.hpp>

auto get_timestamp() -> std::string
{
    const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    const auto timestamp = std::format("{:%Y%m%dT%H%M%SZ}", now);

    return timestamp;
}
struct CommandLineOptions
{
    std::filesystem::path config_file;
    std::filesystem::path output_directory = ".";
    std::string log_level = "info";
};

auto configure_options(CLI::App& app) -> CommandLineOptions
{
    CommandLineOptions options;

    app.add_option(
           "-c,--config_file", options.config_file,
           "Path to a TOML configuration file for running a simulation with BOLT"
    )
        ->required();

    app.add_option(
           "-o,--output_directory", options.output_directory,
           "Path to the output directory for logs and simulation results"
    )
        ->default_str(options.output_directory);

    app.add_option(
           "-l,--log_level", options.log_level,
           "Logging level (trace, debug, info, warning, error, critical)"
    )
        ->default_str(options.log_level);

    return options;
};

auto configure_logger(const std::filesystem::path& output_directory, const std::string& log_level)
    -> quill::Logger*
{
    const std::string timestamp = get_timestamp();

    quill::Backend::start();

    auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("console");
    auto file_sink = quill::Frontend::create_or_get_sink<quill::FileSink>(
        output_directory / std::format("bolt_{}.log", timestamp)
    );
    quill::PatternFormatterOptions formatter_options{
        "%(time)    [%(thread_id)]    %(short_source_location:<32)    %(log_level:<8)    "
        "%(logger:<4)    %(message)",
        "%Y-%m-%dT%H:%M:%S.%QnsZ", quill::Timezone::GmtTime
    };

    quill::Logger* logger = quill::Frontend::create_or_get_logger(
        "bolt", {std::move(console_sink), std::move(file_sink)}, formatter_options
    );

    if (log_level == "trace_l3")
    {
        logger->set_log_level(quill::LogLevel::TraceL3);
    }
    else if (log_level == "trace_l2")
    {
        logger->set_log_level(quill::LogLevel::TraceL2);
    }
    else if (log_level == "trace_l1")
    {
        logger->set_log_level(quill::LogLevel::TraceL1);
    }
    else if (log_level == "debug")
    {
        logger->set_log_level(quill::LogLevel::Debug);
    }
    else if (log_level == "info")
    {
        logger->set_log_level(quill::LogLevel::Info);
    }
    else if (log_level == "notice")
    {
        logger->set_log_level(quill::LogLevel::Notice);
    }
    else if (log_level == "warning")
    {
        logger->set_log_level(quill::LogLevel::Warning);
    }
    else if (log_level == "error")
    {
        logger->set_log_level(quill::LogLevel::Error);
    }
    else if (log_level == "critical")
    {
        logger->set_log_level(quill::LogLevel::Critical);
    }
    else
    {
        std::string error_message = std::format("Invalid log level specified: {}", log_level);
        LOG_ERROR(logger, "{}", error_message);
        throw std::invalid_argument(error_message);
    }
    LOG_INFO(logger, "Log level set to {}", log_level);

    return logger;
}

auto validate_configuration(const toml::table& configuration, quill::Logger* logger) -> void
{
    if (!configuration.contains("start_time"))
    {
        throw std::invalid_argument("Configuration file is missing required key: 'start_time'");
    }
    if (!configuration["start_time"].is_floating_point())
    {
        throw std::invalid_argument(
            "Configuration file key 'start_time' must be a floating point number"
        );
    }

    if (!configuration.contains("time_step"))
    {
        throw std::invalid_argument("Configuration file is missing required key: 'time_step'");
    }
    if (!configuration["time_step"].is_floating_point())
    {
        throw std::invalid_argument(
            "Configuration file key 'time_step' must be a floating point number"
        );
    }
    if (configuration["time_step"].value<double>() <= 0.0)
    {
        throw std::invalid_argument(
            "Configuration file key 'time_step' must be a positive definite floating point number"
        );
    }

    if (!configuration.contains("number_of_steps"))
    {
        throw std::invalid_argument(
            "Configuration file is missing required key: 'number_of_steps'"
        );
    }
    if (!configuration["number_of_steps"].is_integer())
    {
        throw std::invalid_argument("Configuration file key 'number_of_steps' must be an integer");
    }
    if (configuration["number_of_steps"].value<std::size_t>() < 1)
    {
        throw std::invalid_argument(
            "Configuration file key 'number_of_steps' must be a positive integer"
        );
    }
}

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
        validate_configuration(configuration, logger);
    }
    catch (const std::exception& e)
    {
        LOG_ERROR(logger, "Configuration validation failed: {}", e.what());
        return 1;
    }

    return 0;
}
