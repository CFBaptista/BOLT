#pragma once

#include <array>
#include <concepts>
#include <mdspan>
#include <vector>

template <std::floating_point Real, std::size_t... Shape>
class AlignedArray
{
public:
    using value_type = Real;

    static constexpr std::array<std::size_t, sizeof...(Shape)> shape = {Shape...};
    static constexpr std::size_t size = (Shape * ...);

    AlignedArray();
    ~AlignedArray() = default;
    AlignedArray(const AlignedArray&) = delete;
    auto operator=(const AlignedArray&) -> AlignedArray& = delete;
    AlignedArray(AlignedArray&&) noexcept = default;
    auto operator=(AlignedArray&&) noexcept -> AlignedArray& = default;

    auto operator[](std::size_t index) -> Real&;
    auto operator[](std::size_t index) const -> const Real&;

    template <typename... Indices>
    auto operator[](Indices... indices) -> Real&;

    template <typename... Indices>
    auto operator[](Indices... indices) const -> const Real&;

private:
    std::vector<Real> data_;
    std::mdspan<Real, std::extents<std::size_t, Shape...>> view_;
};

#include "lbm/AlignedArray.tpp"
