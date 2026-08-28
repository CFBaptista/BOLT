#pragma once

#include <format>
#include <stdexcept>

#include "bolt/core/Number.hpp"

#include "validation.hpp" // NOLINT(misc-header-include-cycle)

namespace bolt::config
{

template <Number T>
NumberValidator<T>::NumberValidator(const T& value) : value_(value)
{
}

template <Number T>
auto NumberValidator<T>::value() const -> T
{
    return value_;
}

template <Number T>
auto NumberValidator<T>::greater_than(const T& reference) -> NumberValidator&
{
    if (value_ <= reference)
    {
        throw std::invalid_argument(
            std::format("Value {} is not greater than {}", value_, reference)
        );
    }

    return *this;
}

template <Number T>
auto NumberValidator<T>::greater_or_equal(const T& reference) -> NumberValidator&
{
    if (value_ < reference)
    {
        throw std::invalid_argument(
            std::format("Value {} is not greater than or equal to {}", value_, reference)
        );
    }

    return *this;
}

template <Number T>
auto NumberValidator<T>::less_than(const T& reference) -> NumberValidator&
{
    if (value_ >= reference)
    {
        throw std::invalid_argument(std::format("Value {} is not less than {}", value_, reference));
    }

    return *this;
}

template <Number T>
auto NumberValidator<T>::less_or_equal(const T& reference) -> NumberValidator&
{
    if (value_ > reference)
    {
        throw std::invalid_argument(
            std::format("Value {} is not less than or equal to {}", value_, reference)
        );
    }

    return *this;
}

template <Number T>
auto NumberValidator<T>::between(const T& lower, const T& upper) -> NumberValidator&
{
    if (value_ < lower || value_ > upper)
    {
        throw std::invalid_argument(
            std::format("Value {} is not between {} and {}", value_, lower, upper)
        );
    }

    return *this;
}

} // namespace bolt::config
