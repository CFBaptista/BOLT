#pragma once

#include <cstddef>
#include <filesystem>
#include <string>

namespace bolt::app
{

/// @brief Command line options passed by user to the LBM application.
struct CommandLineOptions
{
    /// Path to the configuration file.
    std::filesystem::path config_file;
    /// Output directory for logs and results.
    std::filesystem::path output_directory = ".";
    /// Log level for the logger.
    std::string log_level = "info";
};

/// @brief Settings configured by user in a configuration file read by the LBM application.
struct ConfigurationFileSettings
{
    /// Starting time for the simulation.
    double start_time;
    /// Time step for the simulation.
    double time_step;
    /// Number of time steps for the simulation.
    std::size_t number_of_steps;
};

/// @brief Input and output sub-configuration for the LBM application.
struct IOConfiguration
{
    /// Path to the configuration file.
    std::string configuration_file;
    /// Output directory for logs and results.
    std::string output_directory;
    /// Log level for the logger.
    std::string log_level;
};

/// @brief Time sub-configuration for the LBM application.
struct TimeConfiguration
{
    /// Starting time for the simulation.
    double start_time;
    /// Time step for the simulation.
    double time_step;
    /// Number of time steps for the simulation.
    std::size_t number_of_steps;
};

/// @brief Complete configuration for the LBM application.
struct ApplicationConfiguration
{
    /// Input and output configuration.
    IOConfiguration io{};
    /// Time configuration.
    TimeConfiguration time{};
};

} // namespace bolt::app
