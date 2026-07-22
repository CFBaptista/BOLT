#pragma once

#include <concepts>
#include <cstddef>

#include "array.hpp" // NOLINT(misc-header-include-cycle)

namespace bolt::core
{

template <std::floating_point Real, std::size_t... Shape>
array<Real, Shape...>::array() : data_(size), view_(data_.data(), shape)
{
}

template <std::floating_point Real, std::size_t... Shape>
auto array<Real, Shape...>::operator[](std::size_t index) -> Real&
{
    return data_[index];
}

template <std::floating_point Real, std::size_t... Shape>
auto array<Real, Shape...>::operator[](std::size_t index) const -> const Real&
{
    return data_[index];
}

template <std::floating_point Real, std::size_t... Shape>
template <typename... Indices>
auto array<Real, Shape...>::operator[](Indices... indices) -> Real&
{
    return view_[indices...];
}

template <std::floating_point Real, std::size_t... Shape>
template <typename... Indices>
auto array<Real, Shape...>::operator[](Indices... indices) const -> const Real&
{
    return view_[indices...];
}

} // namespace bolt::core
