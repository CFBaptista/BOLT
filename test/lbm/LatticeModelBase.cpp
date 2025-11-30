#include "lbm/LatticeModelBase.hpp"

#include <array>
#include <cstddef>

#include <catch2/catch_test_macros.hpp>

class ValidLatticeModel : LatticeModelBase
{
public:
    using Real = double;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr auto dimension() -> std::size_t
    {
        return dimension_;
    }

    static constexpr auto size() -> std::size_t
    {
        return size_;
    }

    static constexpr auto velocities() -> std::array<std::array<int, dimension_>, size_>
    {
        return {};
    }

    static constexpr auto weights() -> std::array<Real, size_>
    {
        return {};
    }
};

class NoBase
{
public:
    using Real = double;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr auto dimension() -> std::size_t
    {
        return dimension_;
    }

    static constexpr auto size() -> std::size_t
    {
        return size_;
    }

    static constexpr auto velocities() -> std::array<std::array<int, dimension_>, size_>
    {
        return {};
    }

    static constexpr auto weights() -> std::array<Real, size_>
    {
        return {};
    }
};

class InvalidValueType : LatticeModelBase
{
public:
    using Real = int;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr auto dimension() -> std::size_t
    {
        return dimension_;
    }

    static constexpr auto size() -> std::size_t
    {
        return size_;
    }

    static constexpr auto velocities() -> std::array<std::array<int, dimension_>, size_>
    {
        return {};
    }

    static constexpr auto weights() -> std::array<Real, size_>
    {
        return {};
    }
};

class InvalidDimension : LatticeModelBase
{
public:
    using Real = double;

    static constexpr std::size_t dimension_ = 5;

    static constexpr std::size_t size_ = 7;

    static constexpr auto dimension() -> std::size_t
    {
        return dimension_;
    }

    static constexpr auto size() -> std::size_t
    {
        return size_;
    }

    static constexpr auto velocities() -> std::array<std::array<int, dimension_>, size_>
    {
        return {};
    }

    static constexpr auto weights() -> std::array<Real, size_>
    {
        return {};
    }
};

class InvalidSize : LatticeModelBase
{
public:
    using Real = double;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 0;

    static constexpr auto dimension() -> std::size_t
    {
        return dimension_;
    }

    static constexpr auto size() -> std::size_t
    {
        return size_;
    }

    static constexpr auto velocities() -> std::array<std::array<int, dimension_>, size_>
    {
        return {};
    }

    static constexpr auto weights() -> std::array<Real, size_>
    {
        return {};
    }
};

static_assert(
    LatticeModel<ValidLatticeModel>,
    "ValidLatticeModel should satisfy LatticeModel concept"
);

static_assert(LatticeModel<NoBase>, "NoBase should not satisfy LatticeModel concept");

static_assert(
    !LatticeModel<InvalidValueType>,
    "InvalidValueType should not satisfy LatticeModel concept"
);

static_assert(
    !LatticeModel<InvalidDimension>,
    "InvalidDimension should not satisfy LatticeModel concept"
);

static_assert(!LatticeModel<InvalidSize>, "InvalidSize should not satisfy LatticeModel concept");

TEST_CASE("Dummy test for LatticeModel concept")
{
    REQUIRE(true); // Ensures Catch2 runs this file
}
