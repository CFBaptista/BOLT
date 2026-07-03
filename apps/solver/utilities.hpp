#pragma once

#include <string>

/**
 * @brief Get ISO 8601 formatted timestamp without special characters.
 *
 * @return A string representing the current timestamp in ISO 8601 format without special
 * characters.
 */
auto get_timestamp() -> std::string;
