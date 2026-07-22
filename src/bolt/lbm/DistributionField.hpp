#pragma once

#include <array>
#include <cstddef>

#include "LatticeModel.hpp"
#include "bolt/core/containers/array.hpp"

namespace bolt::lbm
{

/// @brief A class template representing a N-dimensional Cartesian grid containing distributions at
/// each node for a given lattice model.
///
/// @tparam Lattice The lattice model to be used (e.g., D1Q3, D2Q9, D3Q27).
/// @tparam Shape The dimensions of the grid (e.g., 100 for a 1D grid or 30, 50 for a 2D grid or 64,
/// 64, 64 for a 3D grid).
template <LatticeModel Lattice, std::size_t... Shape>
class DistributionField
{
public:
    /// @brief The shape of the grid, i.e., the number of nodes in each dimension.
    static constexpr std::array<std::size_t, sizeof...(Shape)> shape = {Shape...};
    /// @brief The total number of nodes in the grid.
    static constexpr std::size_t grid_size = (Shape * ...);
    /// @brief The size of the distribution at each grid node.
    static constexpr std::size_t lattice_size = Lattice::size;
    /// @brief The spatial dimension of the grid.
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

    /// @brief Default constructor.
    DistributionField() = default;

    /// @brief Destructor.
    ~DistributionField() = default;

    DistributionField(const DistributionField&) = delete;
    auto operator=(const DistributionField&) -> DistributionField& = delete;

    /// @brief Move constructor.
    DistributionField(DistributionField&&) noexcept = default;

    /// @brief Move assignment operator.
    ///
    /// @return A reference to the assigned object.
    auto operator=(DistributionField&&) noexcept -> DistributionField& = default;

    /// @brief Access the distribution for a velocity at a node using a linear index.
    ///
    /// @param index The linear index of the distribution for a velocity at a node.
    ///
    /// @return A reference to the distribution at the specified index.
    auto operator[](std::size_t index) -> Lattice::value_type&;

    /// @brief Access the distribution for a velocity at a node using a linear index (const
    /// version).
    ///
    /// @param index The linear index of the distribution for a velocity at a node.
    ///
    /// @return A const reference to the distribution at the specified index.
    auto operator[](std::size_t index) const -> const Lattice::value_type&;

    /// @brief Access the distribution for a velocity at a node using a multi-dimensional index.
    ///
    /// @param indices The multi-dimensional indices of the distribution for a velocity at a node.
    ///
    /// @return A reference to the distribution at the specified indices.
    template <typename... Indices>
    auto operator[](Indices... indices) -> Lattice::value_type&;

    /// @brief Access the distribution for a velocity at a node using a multi-dimensional index
    /// (const version).
    ///
    /// @param indices The multi-dimensional indices of the distribution for a velocity at a node.
    ///
    /// @return A const reference to the distribution at the specified indices.
    template <typename... Indices>
    auto operator[](Indices... indices) const -> const Lattice::value_type&;

private:
    bolt::array<typename Lattice::value_type, Lattice::size, Shape...> data_;
};

} // namespace bolt::lbm

#include "DistributionField.tpp"
