#include <cstddef>
#include <filesystem>
#include <stdexcept>
#include <string>

#include "bolt/config/ConfigurationManager.hpp"
#include "bolt/config/configuration_types.hpp"

#include "validation.hpp"

namespace bolt::config
{

IOConfiguration::IOConfiguration(ConfigurationManager& configuration_manager)
    : configuration_file(""), output_directory(".")
{
    update_from_config_(configuration_manager);
    bind_to_cli_(configuration_manager);
}

auto IOConfiguration::update_from_config_(const ConfigurationManager& configuration_manager) -> void
{
    log_level = configuration_manager.get_config_value<std::string>("log_level");
}

auto IOConfiguration::bind_to_cli_(ConfigurationManager& configuration_manager) -> void
{
    configuration_manager.add_cli_option(
        "-c,--config_file", configuration_file,
        "Path to a TOML configuration file for running a simulation with BOLT"
    );

    configuration_manager.add_cli_option(
        "-o,--output_directory", output_directory,
        "Path to the output directory for logs and simulation results"
    );

    configuration_manager.add_cli_option(
        "-l,--log_level", log_level, "Logging level (trace, debug, info, warning, error)"
    );
}

auto IOConfiguration::validate() const -> void
{
    DirectoryValidator(output_directory).exists().is_directory().readable().writable();

    FileValidator(configuration_file).exists().is_file().readable();

    if (log_level != "trace" && log_level != "debug" && log_level != "info" &&
        log_level != "warning" && log_level != "error")
    {
        throw std::invalid_argument("Invalid log level: " + log_level);
    }
}

TimeConfiguration::TimeConfiguration(const ConfigurationManager& configuration_manager)
    : start_time(-1.0), time_step(0.0), number_of_steps(0)
{
    update_from_config_(configuration_manager);
}

auto TimeConfiguration::update_from_config_(const ConfigurationManager& configuration_manager)
    -> void
{
    start_time = configuration_manager.get_config_value<double>("start_time");
    time_step = configuration_manager.get_config_value<double>("time_step");
    number_of_steps = configuration_manager.get_config_value<std::size_t>("number_of_steps");
}

auto TimeConfiguration::validate() const -> void
{
    NumberValidator<double>(start_time).greater_or_equal(0.0);
    NumberValidator<double>(time_step).greater_than(0.0);
    NumberValidator<std::size_t>(number_of_steps).greater_than(0);
}

} // namespace bolt::config
