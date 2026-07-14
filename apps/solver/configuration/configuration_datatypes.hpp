#pragma once

#include <cstddef>
#include <filesystem>
#include <string>

/**
 * @brief Command line options for the LBM solver.
 */
struct CommandLineOptions
{
    /** Path to the configuration file. */
    std::filesystem::path config_file;
    /** Output directory for logs and results. */
    std::filesystem::path output_directory = ".";
    /** Log level for the logger. */
    std::string log_level = "info";
};

/**
 * @brief Input and output configuration for the LBM solver.
 */
struct IOConfiguration
{
    /** Path to the configuration file. */
    std::string configuration_file;
    /** Output directory for logs and results. */
    std::string output_directory;
    /** Log level for the logger. */
    std::string log_level;
};

/**
 * @brief Time configuration for the LBM solver.
 */
struct TimeConfiguration
{
    /** Starting time for the simulation. */
    double start_time;
    /** Time step for the simulation. */
    double time_step;
    /** Number of time steps for the simulation. */
    std::size_t number_of_steps;
};

/**
 * @brief Application configuration for the LBM solver.
 */
struct ApplicationConfiguration
{
    /** Input and output configuration. */
    IOConfiguration io{};
    /** Time configuration. */
    TimeConfiguration time{};
};
