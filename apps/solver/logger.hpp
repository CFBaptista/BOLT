#pragma once

#include <filesystem>
#include <string>

#include "quill/Logger.h"

/**
 * @brief Configures a Quill logger for the application.
 *
 * @param output_directory The directory where log files should be stored.
 * @param log_level The logging level (e.g., "trace_l3", "trace_l2", "trace_l1", "debug", "info",
 * "warning", "error", "critical").
 *
 * @return A pointer to the configured quill::Logger instance.
 */
auto configure_logger(const std::filesystem::path& output_directory, const std::string& log_level)
    -> quill::Logger*;
