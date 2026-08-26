#pragma once

#include <filesystem>
#include <string>

#include <quill/Logger.h>

namespace bolt::core
{

/// @brief Configures a Quill logger for the application.
///
/// @param output_directory The directory where log files should be stored.
/// @param log_level The logging level. Available levels are "trace_l1", "debug", "info", "warning",
/// "error".
///
/// @return A pointer to the configured quill::Logger instance.
auto create_logger(const std::filesystem::path& output_directory, const std::string& log_level)
    -> quill::Logger*;

} // namespace bolt::core
