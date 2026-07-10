#pragma once

#include <cstddef>

#include "core/concepts/LatticeModel.hpp"
#include "lbm/DistributionField.hpp" // NOLINT(misc-header-include-cycle)

namespace bolt
{

namespace lbm
{

template <LatticeModel Lattice, std::size_t... Shape>
auto DistributionField<Lattice, Shape...>::operator[](std::size_t index) -> Lattice::value_type&
{
    return data_[index];
}

template <LatticeModel Lattice, std::size_t... Shape>
auto DistributionField<Lattice, Shape...>::operator[](std::size_t index) const
    -> const Lattice::value_type&
{
    return data_[index];
}

template <LatticeModel Lattice, std::size_t... Shape>
template <typename... Indices>
auto DistributionField<Lattice, Shape...>::operator[](Indices... indices) -> Lattice::value_type&
{
    return data_[indices...];
}

template <LatticeModel Lattice, std::size_t... Shape>
template <typename... Indices>
auto DistributionField<Lattice, Shape...>::operator[](Indices... indices) const
    -> const Lattice::value_type&
{
    return data_[indices...];
}

} // namespace lbm

} // namespace bolt
