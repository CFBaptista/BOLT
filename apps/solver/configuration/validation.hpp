#pragma once

#include <string>

#include <toml++/toml.hpp>

/// @brief Validator for numerical configuration settings.
///
/// This class provides a fluent interface for validating numerical values
/// from a TOML configuration table. It supports common validation checks
/// such existence, proper typing and bounds checking.
///
/// @tparam T The type of the numerical value to validate.
template <typename T>
class NumberValidator
{
public:
    /// @brief Construct a NumberValidator for a specific key in a TOML table.
    ///
    /// @param table The TOML table containing the configuration settings.
    /// @param key The key corresponding to the numerical value to validate.
    ///
    /// @throws std::invalid_argument if the key does not exist or the value is not of type T.
    explicit NumberValidator(const toml::table& table, const std::string& key);

    /// @brief Get the validated value.
    ///
    /// @return The validated numerical value.
    auto value() const -> T;

    /// @brief Ensure the value is greater than the given reference.
    ///
    /// @param reference The reference value to compare against.
    ///
    /// @return The NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not greater than the reference.
    auto greater_than(const T& reference) -> NumberValidator&;

    /// @brief Ensure the value is greater than or equal to the given reference.
    ///
    /// @param reference The reference value to compare against.
    ///
    /// @return The NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not greater than or equal to the reference.
    auto greater_or_equal(const T& reference) -> NumberValidator&;

    /// @brief Ensure the value is less than the given reference.
    ///
    /// @param reference The reference value to compare against.
    ///
    /// @return The NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not less than the reference.
    auto less_than(const T& reference) -> NumberValidator&;

    /// @brief Ensure the value is less than or equal to the given reference.
    ///
    /// @param reference The reference value to compare against.
    ///
    /// @return The NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not less than or equal to the reference.
    auto less_or_equal(const T& reference) -> NumberValidator&;

    /// @brief Ensure the value is between the given lower and upper bounds (inclusive).
    ///
    /// @param lower The lower bound.
    /// @param upper The upper bound.
    ///
    /// @return The NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not between the lower and upper bounds
    /// (inclusive).
    auto between(const T& lower, const T& upper) -> NumberValidator&;

private:
    std::string key_;
    T value_;
};

#include "validation.tpp"
