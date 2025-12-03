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

    DensityDistribution() noexcept = default;
    explicit DensityDistribution(const std::array<Real, Model::size()>& distribution) noexcept;
    DensityDistribution(const DensityDistribution& other) noexcept = default;
    DensityDistribution(DensityDistribution&& other) noexcept = default;
    auto operator=(const DensityDistribution& other) noexcept -> DensityDistribution& = default;
    auto operator=(DensityDistribution&& other) noexcept -> DensityDistribution& = default;
    ~DensityDistribution() noexcept = default;

    static constexpr auto dimension() -> std::size_t;

    static constexpr auto size() -> std::size_t;

    auto operator[](std::size_t index) -> Real&;
    auto operator[](std::size_t index) const -> const Real&;

private:
    std::array<Real, Model::size()> distribution_;
};

#include "lbm/DensityDistribution.tpp"
