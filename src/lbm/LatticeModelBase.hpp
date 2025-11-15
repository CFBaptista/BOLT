#pragma once

#include <cstddef>

/**
 * @class LatticeModelBase
 * @brief Class template that specifies the interface for lattice models.
 *
 * This class template specifies the interface for lattice models used in lattice Boltzmann methods.
 * The interface is implemented using CRTP. Derived classes must provide the data specific to a
 * lattice model as static constexpr members.
 *
 * @tparam Derived Lattice model type.
 */
template <typename Derived>
class LatticeModelBase
{
public:
    /**
     * @brief Returns the spatial dimension of a lattice model (e.g. 2 for D2Q9).
     *
     * @return The spatial dimension.
     */
    static constexpr auto dimension() -> std::size_t;

    /**
     * @brief Returns the number of discrete velocity vectors (e.g. 9 for D2Q9).
     *
     * @return The number of discrete velocity vectors.
     */
    static constexpr auto size() -> std::size_t;

    /**
     * @brief Returns the discrete velocity vectors of a lattice model.
     *
     * @return The discrete velocity vectors in lattice units.
     */
    static constexpr auto velocities();

    /**
     * @brief Returns the quadrature weight for each discrete velocity vector.
     *
     * @return The weight for each discrete velocity vector.
     */
    static constexpr auto weights();
};

#include "LatticeModelBase.tpp"
