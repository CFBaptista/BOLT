#pragma once

#include <span>
#include <string_view>

#include <CLI/CLI.hpp>
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include <toml++/toml.hpp>

#include "configuration_datatypes.hpp"

/// @brief Parse command-line arguments and the input configuration file for the LBM solver.
///
/// @param args command-line arguments.
///
/// @return Parsed application configuration.
auto parse_configuration(std::span<const std::string_view> args) -> ApplicationConfiguration;
