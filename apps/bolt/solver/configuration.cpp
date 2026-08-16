#include <span>
#include <string_view>

#include <CLI/CLI.hpp>
#include <toml++/toml.hpp>

#include "bolt/config/configuration_types.hpp"
#include "configuration.hpp"

namespace bolt::app
{

auto parse_configuration(std::span<const std::string_view> args) -> ApplicationConfiguration
{
    CLI::App app{};
    const toml::table table{
        toml::parse_file(bolt::config::get_configuration_filepath(args).string())
    };

    const bolt::config::IOConfiguration io_configuration{table, app};
    const bolt::config::TimeConfiguration time_configuration{table, app};
    bolt::config::parse_cli(app, args);

    io_configuration.validate();
    time_configuration.validate();

    ApplicationConfiguration application_configuration{
        .io = io_configuration,
        .time = time_configuration,
    };

    return application_configuration;
}

} // namespace bolt::app
