#pragma once

#include <span>
#include <string_view>

#include "bolt/config/configuration_types.hpp"

namespace bolt::app
{

/// @brief Complete configuration for the LBM application.
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
struct ApplicationConfiguration
{
    /// Input and output configuration.
    bolt::config::IOConfiguration io;
    /// Time configuration.
    bolt::config::TimeConfiguration time;
};

/// @brief Parse command-line arguments and the input configuration file for the LBM solver.
///
/// @param args command-line arguments.
///
/// @return Parsed application configuration.
auto parse_configuration(std::span<const std::string_view> args) -> ApplicationConfiguration;

} // namespace bolt::app
