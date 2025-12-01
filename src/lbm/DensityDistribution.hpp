#pragma once

#include <array>
#include <cstddef>

#include "lbm/LatticeModelBase.hpp"
#include "lbm/NodeDistributionBase.hpp"

template <LatticeModel Model>
class DensityDistribution : public NodeDistributionBase
{
public:
    using Real = typename Model::Real;

    DensityDistribution<Model>(const std::array<Real, Model::size()>& distribution);
    DensityDistribution<Model>(const DensityDistribution<Model>& other) = delete;
    DensityDistribution<Model>(DensityDistribution<Model>&& other) noexcept = default;
    ~DensityDistribution<Model>() = default;

    static constexpr auto dimension() -> std::size_t;

    static constexpr auto size() -> std::size_t;

    auto operator[](std::size_t index) -> Real&;
    auto operator[](std::size_t index) const -> const Real&;

    auto operator=(const DensityDistribution<Model>& other) -> DensityDistribution<Model>& = delete;
    auto operator=(DensityDistribution<Model>&& other
    ) noexcept -> DensityDistribution<Model>& = default;

private:
    std::array<Real, Model::size()> distribution_;
};

#include "lbm/DensityDistribution.tpp"
