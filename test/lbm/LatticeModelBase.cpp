#include "lbm/LatticeModelBase.hpp"

#include <array>
#include <cstddef>

#include <catch2/catch_test_macros.hpp>

class ValidLatticeModel : LatticeModelBase<ValidLatticeModel>
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

class InvalidValueType : LatticeModelBase<InvalidValueType>
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

class IntDimension : LatticeModelBase<IntDimension>
{
public:
    using Real = double;

    static constexpr int dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr auto dimension() -> int
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

class ZeroDimensional : LatticeModelBase<ZeroDimensional>
{
public:
    using Real = double;

    static constexpr std::size_t dimension_ = 0;

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

class FourDimensional : LatticeModelBase<FourDimensional>
{
public:
    using Real = double;

    static constexpr std::size_t dimension_ = 4;

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

class IntSize : LatticeModelBase<IntSize>
{
public:
    using Real = double;

    static constexpr std::size_t dimension_ = 2;

    static constexpr int size_ = 0;

    static constexpr auto dimension() -> std::size_t
    {
        return dimension_;
    }

    static constexpr auto size() -> int
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

class InvalidSize : LatticeModelBase<InvalidSize>
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

class InvalidDimensionVelocity : LatticeModelBase<InvalidDimensionVelocity>
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

    static constexpr auto velocities() -> std::array<std::array<int, 3>, size_>
    {
        return {};
    }

    static constexpr auto weights() -> std::array<Real, size_>
    {
        return {};
    }
};

class InvalidSizeVelocity : LatticeModelBase<InvalidSizeVelocity>
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

    static constexpr auto velocities() -> std::array<std::array<int, dimension_>, 3>
    {
        return {};
    }

    static constexpr auto weights() -> std::array<Real, size_>
    {
        return {};
    }
};

class InvalidSizeWeight : LatticeModelBase<InvalidSizeWeight>
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

    static constexpr auto weights() -> std::array<Real, 3>
    {
        return {};
    }
};

class InvalidFloatingPointWeight : LatticeModelBase<InvalidFloatingPointWeight>
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

    static constexpr auto velocities() -> std::array<std::array<int, dimension_>, 3>
    {
        return {};
    }

    static constexpr auto weights() -> std::array<float, size_>
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

static_assert(!LatticeModel<IntDimension>, "IntDimension should not satisfy LatticeModel concept");

static_assert(
    !LatticeModel<ZeroDimensional>,
    "ZeroDimensional should not satisfy LatticeModel concept"
);

static_assert(
    !LatticeModel<FourDimensional>,
    "FourDimensional should not satisfy LatticeModel concept"
);

static_assert(!LatticeModel<IntSize>, "IntSize should not satisfy LatticeModel concept");

static_assert(!LatticeModel<InvalidSize>, "InvalidSize should not satisfy LatticeModel concept");

static_assert(
    !LatticeModel<InvalidDimensionVelocity>,
    "InvalidDimensionVelocity should not satisfy LatticeModel concept"
);

static_assert(
    !LatticeModel<InvalidSizeVelocity>,
    "InvalidSizeVelocity should not satisfy LatticeModel concept"
);

static_assert(
    !LatticeModel<InvalidSizeWeight>,
    "InvalidSizeWeight should not satisfy LatticeModel concept"
);

static_assert(
    !LatticeModel<InvalidFloatingPointWeight>,
    "InvalidFloatingPointWeight should not satisfy LatticeModel concept"
);

TEST_CASE("Dummy test for LatticeModel concept")
{
    REQUIRE(true); // Ensures Catch2 runs this file
}
