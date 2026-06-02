#include <cstddef>
#include <stdexcept>

#include <toml++/toml.hpp>

#include "configuration.hpp"

auto validate_configuration(const toml::table& configuration) -> void
{
    if (!configuration.contains("start_time"))
    {
        throw std::invalid_argument("Configuration file is missing required key: 'start_time'");
    }
    if (!configuration["start_time"].is_floating_point())
    {
        throw std::invalid_argument(
            "Configuration file key 'start_time' must be a floating point number"
        );
    }

    if (!configuration.contains("time_step"))
    {
        throw std::invalid_argument("Configuration file is missing required key: 'time_step'");
    }
    if (!configuration["time_step"].is_floating_point())
    {
        throw std::invalid_argument(
            "Configuration file key 'time_step' must be a floating point number"
        );
    }
    if (configuration["time_step"].value<double>() <= 0.0)
    {
        throw std::invalid_argument(
            "Configuration file key 'time_step' must be a positive definite floating point number"
        );
    }

    if (!configuration.contains("number_of_steps"))
    {
        throw std::invalid_argument(
            "Configuration file is missing required key: 'number_of_steps'"
        );
    }
    if (!configuration["number_of_steps"].is_integer())
    {
        throw std::invalid_argument("Configuration file key 'number_of_steps' must be an integer");
    }
    if (configuration["number_of_steps"].value<std::size_t>() < 1)
    {
        throw std::invalid_argument(
            "Configuration file key 'number_of_steps' must be a positive integer"
        );
    }
}
