#pragma once

#include <array>
#include <cstddef>

template <std::size_t... Shape>
class DistributionField
{
public:
    static constexpr std::array<std::size_t, sizeof...(Shape)> shape = {Shape...};
    static constexpr std::size_t size = (Shape * ...);
    static constexpr std::size_t dimension = sizeof...(Shape);

    static_assert(size > 0, "A DistributionField must have a positive size.");
    static_assert(dimension > 0 && dimension < 4, "A DistributionField must be 1D, 2D or 3D.");
};
