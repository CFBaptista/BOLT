#pragma once

#include <format>
#include <stdexcept>
#include <string>

#include <toml++/toml.hpp>

#include "utilities.hpp"
#include "validation.hpp" // NOLINT(misc-header-include-cycle)

namespace bolt::app
{

template <typename T>
NumberValidator<T>::NumberValidator(const toml::table& table, const std::string& key)
    : key_(key), value_(get_toml_value<T>(table, key))
{
}

template <typename T>
auto NumberValidator<T>::value() const -> T
{
    return value_;
}

template <typename T>
auto NumberValidator<T>::greater_than(const T& reference) -> NumberValidator&
{
    if (value_ <= reference)
    {
        throw std::invalid_argument(
            std::format("'{}' value {} is not greater than {}", key_, value_, reference)
        );
    }

    return *this;
}

template <typename T>
auto NumberValidator<T>::greater_or_equal(const T& reference) -> NumberValidator&
{
    if (value_ < reference)
    {
        throw std::invalid_argument(
            std::format("'{}' value {} is not greater than or equal to {}", key_, value_, reference)
        );
    }

    return *this;
}

template <typename T>
auto NumberValidator<T>::less_than(const T& reference) -> NumberValidator&
{
    if (value_ >= reference)
    {
        throw std::invalid_argument(
            std::format("'{}' value {} is not less than {}", key_, value_, reference)
        );
    }

    return *this;
}

template <typename T>
auto NumberValidator<T>::less_or_equal(const T& reference) -> NumberValidator&
{
    if (value_ > reference)
    {
        throw std::invalid_argument(
            std::format("'{}' value {} is not less than or equal to {}", key_, value_, reference)
        );
    }

    return *this;
}

template <typename T>
auto NumberValidator<T>::between(const T& lower, const T& upper) -> NumberValidator&
{
    if (value_ < lower || value_ > upper)
    {
        throw std::invalid_argument(
            std::format("'{}' value {} is not between {} and {}", key_, value_, lower, upper)
        );
    }

    return *this;
}

} // namespace bolt::app
