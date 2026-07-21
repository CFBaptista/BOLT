#include <filesystem>
#include <format>
#include <stdexcept>
#include <string>
#include <utility>

#include <quill/Backend.h>
#include <quill/Frontend.h>
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include <quill/core/Common.h>
#include <quill/core/LogLevel.h>
#include <quill/core/PatternFormatterOptions.h>
#include <quill/sinks/ConsoleSink.h>
#include <quill/sinks/FileSink.h>

#include "logger.hpp"
#include "utilities.hpp"

namespace bolt::app
{

auto configure_logger(const std::filesystem::path& output_directory, const std::string& log_level)
    -> quill::Logger*
{
    const std::string timestamp = get_timestamp();

    quill::Backend::start();

    auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("console");
    auto file_sink = quill::Frontend::create_or_get_sink<quill::FileSink>(
        output_directory / std::format("bolt_{}.log", timestamp)
    );
    const quill::PatternFormatterOptions formatter_options{
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

} // namespace bolt::app
