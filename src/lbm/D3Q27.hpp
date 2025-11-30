#pragma once

#include <array>
#include <concepts>
#include <cstddef>

#include "LatticeModelBase.hpp"

/**
 * @class D3Q27
 * @brief Class template representing the D3Q27 lattice model.
 *
 * This class template contains the data specific to the `D3Q27` lattice model.
 * It provides `static constexpr` methods to access the data.
 * Use the concept `LatticeModel` to restrict template parameters to valid lattice models.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = double>
class D3Q27 : public LatticeModelBase
{
private:
    static constexpr int dimension_{3};

    static constexpr int size_{27};

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{
        {{{0, 0, 0}},   {{1, 0, 0}},   {{-1, 0, 0}},  {{0, 1, 0}},  {{0, -1, 0}},  {{0, 0, 1}},
         {{0, 0, -1}},  {{1, 1, 0}},   {{-1, 1, 0}},  {{1, -1, 0}}, {{-1, -1, 0}}, {{1, 0, 1}},
         {{-1, 0, 1}},  {{1, 0, -1}},  {{-1, 0, -1}}, {{0, 1, 1}},  {{0, -1, 1}},  {{0, 1, -1}},
         {{0, -1, -1}}, {{1, 1, 1}},   {{-1, 1, 1}},  {{1, -1, 1}}, {{-1, -1, 1}}, {{1, 1, -1}},
         {{-1, 1, -1}}, {{1, -1, -1}}, {{-1, -1, -1}}}
    };

    static constexpr std::array<T, size_> weights_{
        static_cast<T>(8) / static_cast<T>(27),  static_cast<T>(2) / static_cast<T>(27),
        static_cast<T>(2) / static_cast<T>(27),  static_cast<T>(2) / static_cast<T>(27),
        static_cast<T>(2) / static_cast<T>(27),  static_cast<T>(2) / static_cast<T>(27),
        static_cast<T>(2) / static_cast<T>(27),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(54),
        static_cast<T>(1) / static_cast<T>(54),  static_cast<T>(1) / static_cast<T>(216),
        static_cast<T>(1) / static_cast<T>(216), static_cast<T>(1) / static_cast<T>(216),
        static_cast<T>(1) / static_cast<T>(216), static_cast<T>(1) / static_cast<T>(216),
        static_cast<T>(1) / static_cast<T>(216), static_cast<T>(1) / static_cast<T>(216),
        static_cast<T>(1) / static_cast<T>(216)
    };

public:
    using Real = T;

    /**
     * @brief Returns the spatial dimension D3Q27 (i.e. 3).
     *
     * @return The spatial dimension.
     */
    static constexpr auto dimension() noexcept -> std::size_t;

    /**
     * @brief Returns the number of discrete velocity vectors for D3Q27 (i.e. 27).
     *
     * @return The number of discrete velocity vectors.
     */
    static constexpr auto size() noexcept -> std::size_t;

    /**
     * @brief Returns the discrete velocity vectors of D3Q27.
     *
     * @return The discrete velocity vectors in lattice units.
     */
    static constexpr auto
    velocities() noexcept -> std::array<std::array<int, D3Q27<T>::dimension_>, D3Q27<T>::size_>;

    /**
     * @brief Returns the quadrature weight for each discrete velocity vector of D3Q27.
     *
     * @return The weight for each discrete velocity vector.
     */
    static constexpr auto weights() noexcept -> std::array<T, D3Q27<T>::size_>;
};

#include "D3Q27.tpp"
