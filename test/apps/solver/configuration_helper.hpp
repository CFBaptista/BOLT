#include <toml++/toml.hpp>

#include "configuration/configuration_datatypes.hpp"

namespace detail
{
auto validate_configuration_file_settings(const toml::table& table) -> ConfigurationFileSettings;
} // namespace detail
