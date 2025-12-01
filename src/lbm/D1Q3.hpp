#pragma once

#include <array>
#include <concepts>
#include <cstddef>

#include "LatticeModelBase.hpp"

/**
 * @class D1Q3
 * @brief Class template representing the D1Q3 lattice model.
 *
 * This class template contains the `static constexpr` data specific to the `D1Q3` lattice model.
 * Accessors are defined in the CRTP base class `LatticeModelBase`. Use the concept `LatticeModel`
 * to constrain the template parameter of consumers of this class.
 *
 * @tparam T The floating-point type.
 */
template <std::floating_point T = double>
class D1Q3 : public LatticeModelBase<D1Q3<T>>
{
public:
    using Real = T;

    friend class LatticeModelBase<D1Q3<T>>;

    D1Q3() = delete;
    D1Q3(const D1Q3&) = delete;
    D1Q3(D1Q3&&) = delete;
    auto operator=(const D1Q3<T>&) -> D1Q3<T>& = delete;
    auto operator=(D1Q3<T>&&) -> D1Q3<T>& = delete;
    ~D1Q3() = delete;

private:
    static constexpr std::size_t dimension_{1};

    static constexpr std::size_t size_{3};

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{
        {{{0}}, {{1}}, {{-1}}}
    };

    static constexpr std::array<T, size_> weights_{
        static_cast<T>(4) / static_cast<T>(6), static_cast<T>(1) / static_cast<T>(6),
        static_cast<T>(1) / static_cast<T>(6)
    };
};
