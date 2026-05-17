#pragma once

#include "lbm/DistributionField.hpp"
#include <cstddef>

template <std::size_t... Shape>
DistributionField<Shape...>::DistributionField() : data_(size, 0.0), view_(data_.data())
{
}

template <std::size_t... Shape>
DistributionField<Shape...>::~DistributionField() = default;

template <std::size_t... Shape>
DistributionField<Shape...>::DistributionField(DistributionField&&) noexcept = default;

template <std::size_t... Shape>
auto DistributionField<Shape...>::operator=(DistributionField&&) noexcept
    -> DistributionField& = default;

template <std::size_t... Shape>
auto DistributionField<Shape...>::operator[](std::size_t index) -> double&
{
    return data_[index];
}

template <std::size_t... Shape>
auto DistributionField<Shape...>::operator[](std::size_t index) const -> const double&
{
    return data_[index];
}

template <std::size_t... Shape>
template <typename... Indices>
auto DistributionField<Shape...>::operator[](Indices... indices) -> double&
{
    return view_[indices...];
}

template <std::size_t... Shape>
template <typename... Indices>
auto DistributionField<Shape...>::operator[](Indices... indices) const -> const double&
{
    return view_[indices...];
}
