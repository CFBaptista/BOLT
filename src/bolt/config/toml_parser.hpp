#pragma once

#include <string_view>

#include <toml++/toml.hpp>

namespace bolt::config
{

/// @brief Gets a value from a TOML table.
///
/// Retrieves a value of type `T` from the TOML table using the specified key. If the key is not
/// found or the value cannot be converted to type `T`, an exception is thrown.
///
/// @tparam T Expected type of the value to retrieve.
///
/// @param table TOML table from which to retrieve a value.
/// @param key Key associated with the value to retrieve.
///
/// @return Value of type `T` associated with the specified key.
///
/// @throws std::invalid_argument if the key is not found or if the value cannot be converted to
/// type `T`.
template <typename T>
auto get_toml_value(const toml::table& table, std::string_view key) -> T;

} // namespace bolt::config

#include "toml_parser.tpp"
