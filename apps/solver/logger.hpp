#pragma once

#include <filesystem>
#include <string>

#include "quill/Logger.h"

auto configure_logger(const std::filesystem::path& output_directory, const std::string& log_level)
    -> quill::Logger*;
