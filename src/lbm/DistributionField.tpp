#pragma once

#include <cstddef>

#include "lbm/DistributionField.hpp"

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
auto DistributionField<Lattice, Shape...>::operator[](Indices... indices) ->
    typename Lattice::value_type&
{
    return data_[indices...];
}

template <LatticeModel Lattice, std::size_t... Shape>
template <typename... Indices>
auto DistributionField<Lattice, Shape...>::operator[](Indices... indices) const -> const
    typename Lattice::value_type&
{
    return data_[indices...];
}
