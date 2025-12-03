#pragma once

#include <cstddef>

#include "lbm/DensityDistribution.hpp"
#include "lbm/LatticeModelBase.hpp"

template <LatticeModel Model>
DensityDistribution<Model>::DensityDistribution(const std::array<Real, Model::size()>& distribution
) noexcept
    : distribution_(distribution)
{
}

template <LatticeModel Model>
constexpr auto DensityDistribution<Model>::dimension() -> std::size_t
{
    return Model::dimension();
}

template <LatticeModel Model>
constexpr auto DensityDistribution<Model>::size() -> std::size_t
{
    return Model::size();
}

template <LatticeModel Model>
auto DensityDistribution<Model>::operator[](std::size_t index) -> Real&
{
    return distribution_[index];
}

template <LatticeModel Model>
auto DensityDistribution<Model>::operator[](std::size_t index) const -> const Real&
{
    return distribution_[index];
}