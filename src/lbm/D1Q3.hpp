#pragma once

#include <array>
#include <concepts>

#include "LatticeModelBase.hpp"

/**
 * @class D1Q3
 * @brief Class template representing the D1Q3 lattice model.
 *
 * This class template contains the data specific to the `D1Q3` lattice model.
 * It provides `static constexpr` methods to access the data.
 * Use the concept `LatticeModel` to restrict template parameters to valid lattice models.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T>
class D1Q3 : public LatticeModelBase
{
private:
    static constexpr int dimension_{1};

    static constexpr int size_{3};

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{
        {{{0}}, {{1}}, {{-1}}}
    };

    static constexpr std::array<T, size_> weights_{
        static_cast<T>(4) / static_cast<T>(6), static_cast<T>(1) / static_cast<T>(6),
        static_cast<T>(1) / static_cast<T>(6)
    };

public:
    using Real = T;

    /**
     * @brief Returns the spatial dimension D1Q3 (i.e. 1).
     *
     * @return The spatial dimension.
     */
    static constexpr auto dimension() -> std::size_t;

    /**
     * @brief Returns the number of discrete velocity vectors for D1Q3 (i.e. 3).
     *
     * @return The number of discrete velocity vectors.
     */
    static constexpr auto size() -> std::size_t;

    /**
     * @brief Returns the discrete velocity vectors of D1Q3.
     *
     * @return The discrete velocity vectors in lattice units.
     */
    static constexpr auto
    velocities() -> std::array<std::array<int, D1Q3<T>::dimension_>, D1Q3<T>::size_>;

    /**
     * @brief Returns the quadrature weight for each discrete velocity vector of D1Q3.
     *
     * @return The weight for each discrete velocity vector.
     */
    static constexpr auto weights() -> std::array<T, D1Q3<T>::size_>;
};

#include "D1Q3.tpp"
