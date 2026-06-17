#pragma once

#include <toml++/toml.hpp>

/**
 * @brief Validates the configuration input for the LBM solver.
 *
 * @param configuration The TOML configuration table to validate
 *
 * @throws std::invalid_argument if the configuration is invalid
 */
auto validate_configuration(const toml::table& configuration) -> void;
