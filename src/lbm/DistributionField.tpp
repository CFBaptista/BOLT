#pragma once

#include "lbm/DistributionField.hpp"
#include <cstddef>

template <LatticeModel Lattice, std::size_t... Shape>
DistributionField<Lattice, Shape...>::DistributionField()
    : data_(Lattice::size * size, 0.0), view_(data_.data())
{
}

template <LatticeModel Lattice, std::size_t... Shape>
DistributionField<Lattice, Shape...>::~DistributionField() = default;

template <LatticeModel Lattice, std::size_t... Shape>
DistributionField<Lattice, Shape...>::DistributionField(DistributionField&&) noexcept = default;

template <LatticeModel Lattice, std::size_t... Shape>
auto DistributionField<Lattice, Shape...>::operator=(DistributionField&&) noexcept
    -> DistributionField& = default;

template <LatticeModel Lattice, std::size_t... Shape>
auto DistributionField<Lattice, Shape...>::operator[](std::size_t index) ->
    typename Lattice::value_type&
{
    return data_[index];
}

template <LatticeModel Lattice, std::size_t... Shape>
auto DistributionField<Lattice, Shape...>::operator[](std::size_t index) const -> const
    typename Lattice::value_type&
{
    return data_[index];
}

template <LatticeModel Lattice, std::size_t... Shape>
template <typename... Indices>
auto DistributionField<Lattice, Shape...>::operator[](std::size_t direction, Indices... indices) ->
    typename Lattice::value_type&
{
    return view_[direction, indices...];
}

template <LatticeModel Lattice, std::size_t... Shape>
template <typename... Indices>
auto DistributionField<Lattice, Shape...>::operator[](
    std::size_t direction,
    Indices... indices
) const -> const typename Lattice::value_type&
{
    return view_[direction, indices...];
}
