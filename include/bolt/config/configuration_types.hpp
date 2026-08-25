#pragma once

#include <cstddef>
#include <filesystem>
#include <string>

#include "ConfigurationManager.hpp"
namespace bolt::config
{

/// @brief Input and output sub-configuration for the LBM application.
class IOConfiguration
{
public:
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)

    /// @brief Path to the configuration file.
    std::filesystem::path configuration_file;
    /// @brief Output directory for logs and results.
    std::filesystem::path output_directory;
    /// @brief Log level for the logger.
    std::string log_level;

    // NOLINTEND(misc-non-private-member-variables-in-classes)

    IOConfiguration() = delete;

    /// @brief Initialize the class using an argument parser.
    ///
    /// @param configuration_manager Argument parser instance to bind options to.
    explicit IOConfiguration(ConfigurationManager& configuration_manager);

    /// @brief Validates the configuration.
    auto validate() const -> void;

private:
    auto update_from_config_(const ConfigurationManager& configuration_manager) -> void;
    auto bind_to_cli_(ConfigurationManager& configuration_manager) -> void;
};

/// @brief Time sub-configuration for the LBM application.
class TimeConfiguration
{
public:
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)

    /// @brief Starting time for the simulation.
    double start_time;
    /// @brief Time step for the simulation.
    double time_step;
    /// @brief Number of time steps for the simulation.
    std::size_t number_of_steps;

    // NOLINTEND(misc-non-private-member-variables-in-classes)

    /// @brief Initialize the class using an argument parser.
    ///
    /// @param configuration_manager Argument parser instance to bind options to.
    explicit TimeConfiguration(ConfigurationManager& configuration_manager);

    /// @brief Validates the configuration.
    auto validate() const -> void;

private:
    auto update_from_config_(const ConfigurationManager& configuration_manager) -> void;
};

} // namespace bolt::config
