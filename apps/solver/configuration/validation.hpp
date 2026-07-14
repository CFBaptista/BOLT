#pragma once

#include <string>

#include <toml++/toml.hpp>

template <typename T>
class NumberValidator
{
public:
    explicit NumberValidator(const toml::table& table, const std::string& key);

    auto value() const -> T;

    auto greater_than(const T& reference) -> NumberValidator&;
    auto greater_or_equal(const T& reference) -> NumberValidator&;
    auto less_than(const T& reference) -> NumberValidator&;
    auto less_or_equal(const T& reference) -> NumberValidator&;
    auto between(const T& lower, const T& upper) -> NumberValidator&;

private:
    std::string key_;
    T value_;
};

#include "validation.tpp"
