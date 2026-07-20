#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <type_traits>

namespace bolt
{

namespace lbm
{

namespace detail
{

template <typename Lattice>
// cppcheck-suppress unusedFunction
consteval auto zero_sum_velocities() -> bool
{
    std::array<int, Lattice::dimension> velocity{0};

    for (std::size_t direction = 0; direction < Lattice::size; ++direction)
    {
        for (std::size_t axis = 0; axis < Lattice::dimension; ++axis)
        {
            velocity[axis] += Lattice::velocities[direction][axis];
        }
    }

    return std::ranges::none_of(velocity, [](int component) -> bool { return component != 0; });
}

template <typename Lattice>
// cppcheck-suppress unusedFunction
consteval auto unit_sum_weights() -> bool
{
    typename Lattice::value_type weight{0};
    const typename Lattice::value_type tolerance{1e-6};

    for (std::size_t direction = 0; direction < Lattice::size; ++direction)
    {
        weight += Lattice::weights[direction];
    }

    return std::abs(weight - typename Lattice::value_type{1}) < tolerance;
}

template <typename Lattice>
concept HasFloatingPointValueType = requires {
    typename Lattice::value_type;
    requires std::floating_point<typename Lattice::value_type>;
};

template <typename Lattice>
concept HasValidDimension = requires {
    requires std::same_as<std::remove_cvref_t<decltype((Lattice::dimension))>, std::size_t>;
    requires(1 <= Lattice::dimension && Lattice::dimension <= 3);
};

template <typename Lattice>
concept HasValidLatticeSize = requires {
    requires std::same_as<std::remove_cvref_t<decltype((Lattice::size))>, std::size_t>;
    requires Lattice::size > 0;
};

template <typename Lattice>
concept HasValidLatticeVelocities =
    HasValidDimension<Lattice> && HasValidLatticeSize<Lattice> && requires {
        requires std::same_as<
            std::remove_cvref_t<decltype((Lattice::velocities))>,
            std::array<std::array<int, Lattice::dimension>, Lattice::size>>;
    } && zero_sum_velocities<Lattice>();

template <typename Lattice>
concept HasValidLatticeWeights =
    HasFloatingPointValueType<Lattice> && HasValidLatticeSize<Lattice> && requires {
        requires std::same_as<
            std::remove_cvref_t<decltype((Lattice::weights))>,
            std::array<typename Lattice::value_type, Lattice::size>>;
    } && unit_sum_weights<Lattice>();

template <typename Lattice>
concept HasValidLatticeSoundSpeed = HasFloatingPointValueType<Lattice> && requires {
    requires std::same_as<
        std::remove_cvref_t<decltype((Lattice::sound_speed_inverse_squared))>,
        typename Lattice::value_type>;
    requires(Lattice::sound_speed_inverse_squared > typename Lattice::value_type{0});
};

} // namespace detail

/// @brief Concept that defines the requirements for a lattice model.
///
/// A LatticeModel must have a floating-point value type, a valid dimension (1D, 2D or 3D), a
/// positive lattice size, zero-sum velocities, unit-sum weights and a positive inverse squared
/// sound speed.
///
/// @tparam Lattice The lattice model to be checked.
template <typename Lattice>
concept LatticeModel = bolt::lbm::detail::HasFloatingPointValueType<Lattice> &&
                       bolt::lbm::detail::HasValidDimension<Lattice> &&
                       bolt::lbm::detail::HasValidLatticeSize<Lattice> &&
                       bolt::lbm::detail::HasValidLatticeVelocities<Lattice> &&
                       bolt::lbm::detail::HasValidLatticeWeights<Lattice> &&
                       bolt::lbm::detail::HasValidLatticeSoundSpeed<Lattice>;

} // namespace lbm

} // namespace bolt
