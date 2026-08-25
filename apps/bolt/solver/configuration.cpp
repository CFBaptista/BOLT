#include <span>
#include <string_view>

#include "bolt/config/configuration_types.hpp"

#include "configuration.hpp"

namespace bolt::app
{

auto parse_configuration(std::span<const std::string_view> args) -> ApplicationConfiguration
{
    bolt::config::ConfigurationManager configuration_manager{args};

    const bolt::config::IOConfiguration io_configuration{configuration_manager};
    const bolt::config::TimeConfiguration time_configuration{configuration_manager};

    configuration_manager.parse();

    io_configuration.validate();
    time_configuration.validate();

    ApplicationConfiguration application_configuration{
        .io = io_configuration,
        .time = time_configuration,
    };

    return application_configuration;
}

} // namespace bolt::app
