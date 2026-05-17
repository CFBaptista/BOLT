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

    static_assert(size > 0, "A DistributionField must have a positive size.");
    static_assert(dimension > 0 && dimension < 4, "A DistributionField must be 1D, 2D or 3D.");

    DistributionField() : data_(size), view_(data_.data()) {};

    auto operator[](std::size_t index) -> double&
    {
        return data_[index];
    }

    auto operator[](std::size_t index) const -> const double&
    {
        return data_[index];
    }

    template <typename... Indices>
    auto operator[](Indices... indices) -> double&
    {
        return view_[indices...];
    }

    template <typename... Indices>
    auto operator[](Indices... indices) const -> const double&
    {
        return view_[indices...];
    }

private:
    std::vector<double> data_;
    std::mdspan<double, std::extents<std::size_t, Shape...>> view_;
};
