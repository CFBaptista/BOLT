#include <array>
#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include "lbm/LatticeModelBase.hpp"

class ValidLatticeModel : public LatticeModelBase<ValidLatticeModel>
{
public:
    using Real = double;

    friend class LatticeModelBase<ValidLatticeModel>;

    static constexpr std::size_t dimension_{2};

    static constexpr std::size_t size_{7};

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class NoBase
{
public:
    using Real = double;

    friend class LatticeModelBase<NoBase>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class InvalidValueType : public LatticeModelBase<InvalidValueType>
{
public:
    using Real = int;

    friend class LatticeModelBase<InvalidValueType>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class ZeroDimensional : public LatticeModelBase<ZeroDimensional>
{
public:
    using Real = double;

    friend class LatticeModelBase<ZeroDimensional>;

    static constexpr std::size_t dimension_ = 0;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class FourDimensional : public LatticeModelBase<FourDimensional>
{
public:
    using Real = double;

    friend class LatticeModelBase<FourDimensional>;

    static constexpr std::size_t dimension_ = 4;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class IntSize : public LatticeModelBase<IntSize>
{
public:
    using Real = double;

    friend class LatticeModelBase<IntSize>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr int size_ = 0;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class InvalidSize : public LatticeModelBase<InvalidSize>
{
public:
    using Real = double;

    friend class LatticeModelBase<InvalidSize>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 0;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class InvalidFloatingPointWeight : public LatticeModelBase<InvalidFloatingPointWeight>
{
public:
    using Real = char;

    friend class LatticeModelBase<InvalidFloatingPointWeight>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

static_assert(
    LatticeModel<ValidLatticeModel>,
    "ValidLatticeModel should satisfy LatticeModel concept"
);

static_assert(!LatticeModel<NoBase>, "NoBase should not satisfy LatticeModel concept");

static_assert(
    !LatticeModel<InvalidValueType>,
    "InvalidValueType should not satisfy LatticeModel concept"
);

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
    !LatticeModel<InvalidFloatingPointWeight>,
    "InvalidFloatingPointWeight should not satisfy LatticeModel concept"
);

TEST_CASE("Dummy test for LatticeModel concept")
{
    REQUIRE(true); // Ensures Catch2 runs this file
}
