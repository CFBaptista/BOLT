#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <mdspan>
#include <vector>

template <typename Lattice>
concept LatticeModel = requires {
    requires std::floating_point<typename Lattice::value_type>;
    requires std::same_as<std::remove_cvref_t<decltype((Lattice::dimension))>, std::size_t>;
    requires(1 <= Lattice::dimension && Lattice::dimension <= 3);
    requires std::same_as<std::remove_cvref_t<decltype((Lattice::size))>, std::size_t>;
    requires Lattice::dimension > 0;
    requires std::same_as<
        std::remove_cvref_t<decltype((Lattice::velocities))>,
        std::array<std::array<int, Lattice::dimension>, Lattice::size>>;
    requires std::same_as<
        std::remove_cvref_t<decltype((Lattice::weights))>,
        std::array<typename Lattice::value_type, Lattice::size>>;
    requires std::same_as<
        std::remove_cvref_t<decltype((Lattice::sound_speed_inverse_squared))>,
        typename Lattice::value_type>;
};

template <std::floating_point Real>
class D1Q3
{
public:
    using value_type = Real;

    D1Q3() = delete;
    ~D1Q3() = delete;
    D1Q3(const D1Q3& other) = delete;
    auto operator=(const D1Q3& other) -> D1Q3& = delete;
    D1Q3(D1Q3&& other) = delete;
    auto operator=(D1Q3&& other) -> D1Q3& = delete;

    static constexpr std::size_t dimension = 1;
    static constexpr std::size_t size = 3;

    static constexpr std::array<std::array<int, dimension>, size> velocities{
        {{{0}}, {{1}}, {{-1}}}
    };

    static constexpr std::array<Real, size> weights{
        static_cast<Real>(4) / static_cast<Real>(6), static_cast<Real>(1) / static_cast<Real>(6),
        static_cast<Real>(1) / static_cast<Real>(6)
    };

    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};

template <std::floating_point Real>
class D2Q9
{
public:
    using value_type = Real;

    D2Q9() = delete;
    ~D2Q9() = delete;
    D2Q9(const D2Q9& other) = delete;
    auto operator=(const D2Q9& other) -> D2Q9& = delete;
    D2Q9(D2Q9&& other) = delete;
    auto operator=(D2Q9&& other) -> D2Q9& = delete;

    static constexpr std::size_t dimension{2};
    static constexpr std::size_t size = 9;

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

    static constexpr std::array<Real, size> weights{
        static_cast<Real>(4) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(9),
        static_cast<Real>(1) / static_cast<Real>(9),  static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36), static_cast<Real>(1) / static_cast<Real>(36),
        static_cast<Real>(1) / static_cast<Real>(36)

    };

    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};

template <std::floating_point Real>
class D3Q27
{
public:
    using value_type = Real;

    D3Q27() = delete;
    ~D3Q27() = delete;
    D3Q27(const D3Q27& other) = delete;
    auto operator=(const D3Q27& other) -> D3Q27& = delete;
    D3Q27(D3Q27&& other) = delete;
    auto operator=(D3Q27&& other) -> D3Q27& = delete;

    static constexpr std::size_t dimension = 3;
    static constexpr std::size_t size = 27;

    static constexpr std::array<std::array<int, dimension>, size> velocities{
        {{{0, 0, 0}},   {{1, 0, 0}},   {{-1, 0, 0}},  {{0, 1, 0}},  {{0, -1, 0}},  {{0, 0, 1}},
         {{0, 0, -1}},  {{1, 1, 0}},   {{-1, 1, 0}},  {{1, -1, 0}}, {{-1, -1, 0}}, {{1, 0, 1}},
         {{-1, 0, 1}},  {{1, 0, -1}},  {{-1, 0, -1}}, {{0, 1, 1}},  {{0, -1, 1}},  {{0, 1, -1}},
         {{0, -1, -1}}, {{1, 1, 1}},   {{-1, 1, 1}},  {{1, -1, 1}}, {{-1, -1, 1}}, {{1, 1, -1}},
         {{-1, 1, -1}}, {{1, -1, -1}}, {{-1, -1, -1}}}

    };

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

    static constexpr Real sound_speed_inverse_squared{static_cast<Real>(3)};
};

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

    DistributionField();
    ~DistributionField();
    DistributionField(const DistributionField&) = delete;
    auto operator=(const DistributionField&) -> DistributionField& = delete;
    DistributionField(DistributionField&&) noexcept;
    auto operator=(DistributionField&&) noexcept -> DistributionField&;

    auto operator[](std::size_t index) -> Lattice::value_type&;
    auto operator[](std::size_t index) const -> const Lattice::value_type&;

    template <typename... Indices>
    auto operator[](std::size_t direction, Indices... indices) -> Lattice::value_type&;

    template <typename... Indices>
    auto operator[](std::size_t direction, Indices... indices) const -> const Lattice::value_type&;

private:
    std::vector<typename Lattice::value_type> data_;
    std::mdspan<typename Lattice::value_type, std::extents<std::size_t, Lattice::size, Shape...>>
        view_;
};

#include "lbm/DistributionField.tpp"
