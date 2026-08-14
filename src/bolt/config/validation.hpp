#pragma once

#include "bolt/core/Number.hpp"

namespace bolt::config
{

/// @brief Stores a value of type `T` and provides methods to validate it.
///
/// Provides an interface for validating numerical values by means of chaining operations. Supports
/// common validation checks such as existence, proper typing, and bounds checking.
///
/// @tparam T Type of the value to validate.
template <Number T>
class NumberValidator
{
public:
    /// @brief Constructs a number validator for a value of type `T`.
    ///
    /// @param value Value to validate.
    ///
    /// @throws std::invalid_argument if the value is not of type `T`.
    explicit NumberValidator(const T& value);

    /// @brief Gets the stored value.
    ///
    /// @return Value of type `T`.
    auto value() const -> T;

    /// @brief Ensures the value is greater than the given reference.
    ///
    /// @param reference Value to compare against.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not greater than the reference.
    auto greater_than(const T& reference) -> NumberValidator&;

    /// @brief Ensures the value is greater than or equal to the given reference.
    ///
    /// @param reference Value to compare against.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not greater than or equal to the reference.
    auto greater_or_equal(const T& reference) -> NumberValidator&;

    /// @brief Ensures the value is less than the given reference.
    ///
    /// @param reference Value to compare against.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not less than the reference.
    auto less_than(const T& reference) -> NumberValidator&;

    /// @brief Ensures the value is less than or equal to the given reference.
    ///
    /// @param reference Value to compare against.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not less than or equal to the reference.
    auto less_or_equal(const T& reference) -> NumberValidator&;

    /// @brief Ensures the value is between the given lower and upper bounds (inclusive).
    ///
    /// @param lower Lower bound.
    /// @param upper Upper bound.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not between the lower and upper bounds
    /// (inclusive).
    auto between(const T& lower, const T& upper) -> NumberValidator&;

private:
    T value_;
};

} // namespace bolt::config

#include "validation.tpp"
