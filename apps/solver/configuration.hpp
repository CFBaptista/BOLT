#pragma once

#include <toml++/impl/parse_error.hpp>
#include <toml++/impl/parser.hpp>
#include <toml++/impl/table.hpp>
#include <toml++/toml.hpp>

auto validate_configuration(const toml::table& configuration) -> void;
