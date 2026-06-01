#include <chrono>
#include <cstddef>
#include <filesystem>
#include <format>
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

auto main(int argc, char* argv[]) -> int
{
    const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    const auto timestamp = std::format("{:%Y%m%dT%H%M%SZ}", now);

    CLI::App app{"BOLT (Boltzmann Operator Lattice Toolkit) is a C++ library for Computational "
                 "Fluid Dynamics based on the Lattice Boltzmann Method."};

    std::filesystem::path config_file;
    app.add_option(
           "-c,--config_file", config_file,
           "Path to a TOML configuration file for running a simulation with BOLT"
    )
        ->required();

    std::filesystem::path output_directory = ".";
    app.add_option(
           "-o,--output_directory", output_directory,
           "Path to the output directory for logs and simulation results"
    )
        ->default_str(output_directory);

    std::string log_level = "info";
    app.add_option(
           "-l,--log_level", log_level,
           "Logging level (trace, debug, info, warning, error, critical)"
    )
        ->default_str(log_level);

    CLI11_PARSE(app, argc, argv);

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
        LOG_ERROR(logger, "Invalid log level specified: {}", log_level);
        return 1;
    }
    LOG_INFO(logger, "Log level set to {}", log_level);

    toml::table configuration;

    try
    {
        LOG_INFO(logger, "Parsing configuration file");

        configuration = toml::parse_file(config_file.string());

        LOG_INFO(logger, "Configuration file parsed successfully");
    }
    catch (const toml::parse_error& e)
    {
        LOG_ERROR(logger, "Failed to parse configuration file:\n{}", e.what());
        return 1;
    }

    if (!configuration.contains("start_time"))
    {
        LOG_ERROR(logger, "Configuration file is missing required key: 'start_time'");
        return 1;
    }
    if (!configuration["start_time"].is_floating_point())
    {
        LOG_ERROR(logger, "Configuration file key 'start_time' must be a floating point number");
        return 1;
    }

    if (!configuration.contains("time_step"))
    {
        LOG_ERROR(logger, "Configuration file is missing required key: 'time_step'");
        return 1;
    }
    if (!configuration["time_step"].is_floating_point())
    {
        LOG_ERROR(logger, "Configuration file key 'time_step' must be a floating point number");
        return 1;
    }
    if (configuration["time_step"].value<double>() <= 0.0)
    {
        LOG_ERROR(
            logger,
            "Configuration file key 'time_step' must be a positive definite floating point number"
        );
        return 1;
    }

    if (!configuration.contains("number_of_steps"))
    {
        LOG_ERROR(logger, "Configuration file is missing required key: 'number_of_steps'");
        return 1;
    }
    if (!configuration["number_of_steps"].is_integer())
    {
        LOG_ERROR(logger, "Configuration file key 'number_of_steps' must be an integer");
        return 1;
    }
    if (configuration["number_of_steps"].value<std::size_t>() < 1)
    {
        LOG_ERROR(logger, "Configuration file key 'number_of_steps' must be a positive integer");
        return 1;
    }

    return 0;
}
