#pragma once

#include <array>
#include <concepts>
#include <cstddef>

#include "LatticeModelBase.hpp"

/**
 * @class D3Q27
 * @brief Class template representing the D3Q27 lattice model.
 *
 * This class template contains the `static constexpr` data specific to the `D3Q27` lattice model.
 * Accessors are defined in the CRTP base class `LatticeModelBase`. Use the concept `LatticeModel`
 * to constrain the template parameter of consumers of this class.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = double>
class D3Q27 : public LatticeModelBase<D3Q27<T>>
{
public:
    using Real = T;

    friend class LatticeModelBase<D3Q27<T>>;

    D3Q27() = delete;
    D3Q27(const D3Q27&) = delete;
    D3Q27(D3Q27&&) = delete;
    auto operator=(const D3Q27<T>&) -> D3Q27<T>& = delete;
    auto operator=(D3Q27<T>&&) -> D3Q27<T>& = delete;
    ~D3Q27() = delete;

private:
    static constexpr std::size_t dimension_{3};

    static constexpr std::size_t size_{27};

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
};