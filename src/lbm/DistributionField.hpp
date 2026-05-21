#pragma once

#include <array>
#include <cstddef>

#include "base/AlignedArray.hpp"
#include "lbm/LatticeModel.hpp"

template <LatticeModel Lattice, std::size_t... Shape>
class DistributionField
{
public:
    static constexpr std::array<std::size_t, sizeof...(Shape)> shape = {Shape...};
    static constexpr std::size_t grid_size = (Shape * ...);
    static constexpr std::size_t lattice_size = Lattice::size;
    static constexpr std::size_t dimension = sizeof...(Shape);

    static_assert(sizeof...(Shape) > 0, "A DistributionField must have a positive size.");
    static_assert(
        sizeof...(Shape) > 0 && sizeof...(Shape) < 4,
        "A DistributionField must be 1D, 2D or 3D."
    );
    static_assert(
        sizeof...(Shape) == Lattice::dimension,
        "The dimension of the DistributionField must match the dimension of the LatticeModel."
    );

    DistributionField() = default;
    ~DistributionField() = default;
    DistributionField(const DistributionField&) = delete;
    auto operator=(const DistributionField&) -> DistributionField& = delete;
    DistributionField(DistributionField&&) noexcept = default;
    auto operator=(DistributionField&&) noexcept -> DistributionField& = default;

    auto operator[](std::size_t index) -> Lattice::value_type&;
    auto operator[](std::size_t index) const -> const Lattice::value_type&;

    template <typename... Indices>
    auto operator[](Indices... indices) -> Lattice::value_type&;

    template <typename... Indices>
    auto operator[](Indices... indices) const -> const Lattice::value_type&;

private:
    AlignedArray<typename Lattice::value_type, Lattice::size, Shape...> data_;
};

#include "lbm/DistributionField.tpp"
