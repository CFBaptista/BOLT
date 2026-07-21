#include <toml++/toml.hpp>

#include "bolt/solver/configuration/configuration_datatypes.hpp"

namespace bolt::app::detail
{

auto validate_configuration_file_settings(const toml::table& table) -> ConfigurationFileSettings;

} // namespace bolt::app::detail
