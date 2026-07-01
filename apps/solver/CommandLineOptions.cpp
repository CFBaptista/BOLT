#include <CLI/CLI.hpp>

#include "CommandLineOptions.hpp"

auto configure_options(CLI::App& app, CommandLineOptions& options) -> void
{
    app.add_option(
           "-c,--config_file", options.config_file,
           "Path to a TOML configuration file for running a simulation with BOLT"
    )
        ->required();

    app.add_option(
           "-o,--output_directory", options.output_directory,
           "Path to the output directory for logs and simulation results"
    )
        ->default_str(options.output_directory);

    app.add_option(
           "-l,--log_level", options.log_level,
           "Logging level (trace, debug, info, warning, error, critical)"
    )
        ->default_str(options.log_level);
}
