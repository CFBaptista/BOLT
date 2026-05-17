#pragma once

#include <array>
#include <cstddef>
#include <mdspan>
#include <vector>

template <std::size_t... Shape>
class DistributionField
{
public:
    static constexpr std::array<std::size_t, sizeof...(Shape)> shape = {Shape...};
    static constexpr std::size_t size = (Shape * ...);
    static constexpr std::size_t dimension = sizeof...(Shape);

    static_assert(sizeof...(Shape) > 0, "A DistributionField must have a positive size.");
    static_assert(
        sizeof...(Shape) > 0 && sizeof...(Shape) < 4,
        "A DistributionField must be 1D, 2D or 3D."
    );

    DistributionField();
    ~DistributionField();
    DistributionField(const DistributionField&) = delete;
    auto operator=(const DistributionField&) -> DistributionField& = delete;
    DistributionField(DistributionField&&) noexcept;
    auto operator=(DistributionField&&) noexcept -> DistributionField&;

    auto operator[](std::size_t index) -> double&;
    auto operator[](std::size_t index) const -> const double&;

    template <typename... Indices>
    auto operator[](Indices... indices) -> double&;

    template <typename... Indices>
    auto operator[](Indices... indices) const -> const double&;

private:
    std::vector<double> data_;
    std::mdspan<double, std::extents<std::size_t, Shape...>> view_;
};

#include "lbm/DistributionField.tpp"
