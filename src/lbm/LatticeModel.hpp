#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <type_traits>

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

/**
 * @brief Concept that defines the requirements for a lattice model..
 *
 * A LatticeModel must have a floating-point value type, a valid dimension (1D, 2D or 3D), a
 * positive lattice size, zero-sum velocities, unit-sum weights and a positive inverse squared sound
 * speed.
 *
 * @tparam Lattice The lattice model to be checked.
 */
template <typename Lattice>
concept LatticeModel = HasFloatingPointValueType<Lattice> && HasValidDimension<Lattice> &&
                       HasValidLatticeSize<Lattice> && HasValidLatticeVelocities<Lattice> &&
                       HasValidLatticeWeights<Lattice> && HasValidLatticeSoundSpeed<Lattice>;

/**
 * @brief A class template representing the D1Q3 lattice model.
 *
 * @tparam Real The floating-point value types.
 */
template <std::floating_point Real>
class D1Q3
{
public:
    /**
     * @brief The floating-point type value type.
     */
    using value_type = Real;

    D1Q3() = delete;
    ~D1Q3() = delete;
    D1Q3(const D1Q3& other) = delete;
    auto operator=(const D1Q3& other) -> D1Q3& = delete;
    D1Q3(D1Q3&& other) = delete;
    auto operator=(D1Q3&& other) -> D1Q3& = delete;

    /**
     * @brief The spatial dimension of the lattice model (1D).
     */
    static constexpr std::size_t dimension = 1;
    /**
     * @brief The number of discrete velocities in the lattice model.
     */
    static constexpr std::size_t size = 3;

    /**
     * @brief The discrete velocities of the lattice model.
     */
    static constexpr std::array<std::array<int, dimension>, size> velocities{
        {{{0}}, {{1}}, {{-1}}}
    };

    /**
     * @brief The weights associated with each discrete velocity.
     */
    static constexpr std::array<Real, size> weights{
        static_cast<Real>(4) / static_cast<Real>(6), static_cast<Real>(1) / static_cast<Real>(6),
        static_cast<Real>(1) / static_cast<Real>(6)
    };

    /**
     * @brief The inverse squared sound speed for the lattice model.
     */
    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};

/**
 * @brief A class template representing the D2Q9 lattice model.
 *
 * @tparam Real The floating-point value types.
 */
template <std::floating_point Real>
class D2Q9
{
public:
    /**
     * @brief The floating-point type value type.
     */
    using value_type = Real;

    D2Q9() = delete;
    ~D2Q9() = delete;
    D2Q9(const D2Q9& other) = delete;
    auto operator=(const D2Q9& other) -> D2Q9& = delete;
    D2Q9(D2Q9&& other) = delete;
    auto operator=(D2Q9&& other) -> D2Q9& = delete;

    /**
     * @brief The spatial dimension of the lattice model (2D).
     */
    static constexpr std::size_t dimension{2};
    /**
     * @brief The number of discrete velocities in the lattice model.
     */
    static constexpr std::size_t size = 9;

    /**
     * @brief The discrete velocities of the lattice model.
     */
    static constexpr std::array<std::array<int, dimension>, size> velocities{
        {{{0, 0}},
         {{1, 0}},
         {{0, 1}},
         {{-1, 0}},
         {{0, -1}},
         {{1, 1}},
         {{-1, 1}},
         {{-1, -1}},
         {{1, -1}}}

    };

    /**
     * @brief The weights associated with each discrete velocity.
     */
    static constexpr std::array<Real, size> weights{
        static_cast<Real>(4) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36), static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36)

    };

    /**
     * @brief The inverse squared sound speed for the lattice model.
     */
    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};

/**
 * @brief A class template representing the D3Q27 lattice model.
 *
 * @tparam Real The floating-point value types.
 */
template <std::floating_point Real>
class D3Q27
{
public:
    /**
     * @brief The floating-point type value type.
     */
    using value_type = Real;

    D3Q27() = delete;
    ~D3Q27() = delete;
    D3Q27(const D3Q27& other) = delete;
    auto operator=(const D3Q27& other) -> D3Q27& = delete;
    D3Q27(D3Q27&& other) = delete;
    auto operator=(D3Q27&& other) -> D3Q27& = delete;

    /**
     * @brief The spatial dimension of the lattice model (3D).
     */
    static constexpr std::size_t dimension = 3;
    /**
     * @brief The number of discrete velocities in the lattice model.
     */
    static constexpr std::size_t size = 27;

    /**
     * @brief The discrete velocities of the lattice model.
     */
    static constexpr std::array<std::array<int, dimension>, size> velocities{
        {{{0, 0, 0}},   {{1, 0, 0}},   {{-1, 0, 0}},  {{0, 1, 0}},  {{0, -1, 0}},  {{0, 0, 1}},
         {{0, 0, -1}},  {{1, 1, 0}},   {{-1, 1, 0}},  {{1, -1, 0}}, {{-1, -1, 0}}, {{1, 0, 1}},
         {{-1, 0, 1}},  {{1, 0, -1}},  {{-1, 0, -1}}, {{0, 1, 1}},  {{0, -1, 1}},  {{0, 1, -1}},
         {{0, -1, -1}}, {{1, 1, 1}},   {{-1, 1, 1}},  {{1, -1, 1}}, {{-1, -1, 1}}, {{1, 1, -1}},
         {{-1, 1, -1}}, {{1, -1, -1}}, {{-1, -1, -1}}}

    };

    /**
     * @brief The weights associated with each discrete velocity.
     */
    static constexpr std::array<Real, size> weights{
        static_cast<Real>(8) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(2) / static_cast<Real>(27),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(54),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216),
        static_cast<Real>(1) / static_cast<Real>(216)

    };

    /**
     * @brief The inverse squared sound speed for the lattice model.
     */
    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};
