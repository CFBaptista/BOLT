#pragma once

#include <format>
#include <stdexcept>
#include <string>
#include <string_view>

#include <toml++/toml.hpp>

/**
 * @brief Get ISO 8601 formatted timestamp without special characters.
 *
 * @return A string representing the current timestamp in ISO 8601 format without special
 * characters.
 */
auto get_timestamp() -> std::string;

/**
 * @brief Get a value from a TOML table with error handling.
 *
 * This function retrieves a value of type `T` from the provided TOML table using the specified
 * key. If the key is not found or the value cannot be converted to type `T`, an exception is
 * thrown.
 *
 * @tparam T The expected type of the value to retrieve.
 *
 * @param table The TOML table from which to retrieve the value.
 * @param key The key corresponding to the desired value in the TOML table.
 *
 * @return The value of type `T` associated with the specified key.
 *
 * @throws std::invalid_argument if the key is not found or if the value cannot be converted to
 * type `T`.
 */
template <typename T>
auto get_toml_value(const toml::table& table, std::string_view key) -> T
{
    if (const auto value = table[key].value<T>(); value)
    {
        return *value;
    }

    throw std::invalid_argument(std::format("Missing or invalid TOML value for key: {}", key));
}
