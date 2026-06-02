#pragma once

#include <toml++/toml.hpp>

auto validate_configuration(const toml::table& configuration) -> void;
