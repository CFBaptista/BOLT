#include <array>
#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include "lbm/VelocitySetBase.hpp"

class ValidVelocitySet : public VelocitySetBase<ValidVelocitySet>
{
public:
    using Real = double;

    friend class VelocitySetBase<ValidVelocitySet>;

    static constexpr std::size_t dimension_{2};

    static constexpr std::size_t size_{7};

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class NoBase
{
public:
    using Real = double;

    friend class VelocitySetBase<NoBase>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class InvalidValueType : public VelocitySetBase<InvalidValueType>
{
public:
    using Real = int;

    friend class VelocitySetBase<InvalidValueType>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class ZeroDimensional : public VelocitySetBase<ZeroDimensional>
{
public:
    using Real = double;

    friend class VelocitySetBase<ZeroDimensional>;

    static constexpr std::size_t dimension_ = 0;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class FourDimensional : public VelocitySetBase<FourDimensional>
{
public:
    using Real = double;

    friend class VelocitySetBase<FourDimensional>;

    static constexpr std::size_t dimension_ = 4;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class IntSize : public VelocitySetBase<IntSize>
{
public:
    using Real = double;

    friend class VelocitySetBase<IntSize>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr int size_ = 0;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class InvalidSize : public VelocitySetBase<InvalidSize>
{
public:
    using Real = double;

    friend class VelocitySetBase<InvalidSize>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 0;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

class InvalidFloatingPointWeight : public VelocitySetBase<InvalidFloatingPointWeight>
{
public:
    using Real = char;

    friend class VelocitySetBase<InvalidFloatingPointWeight>;

    static constexpr std::size_t dimension_ = 2;

    static constexpr std::size_t size_ = 7;

    static constexpr std::array<std::array<int, dimension_>, size_> velocities_{};

    static constexpr std::array<Real, size_> weights_{};
};

static_assert(VelocitySet<ValidVelocitySet>, "ValidVelocitySet should satisfy VelocitySet concept");

static_assert(!VelocitySet<NoBase>, "NoBase should not satisfy VelocitySet concept");

static_assert(
    !VelocitySet<InvalidValueType>,
    "InvalidValueType should not satisfy VelocitySet concept"
);

static_assert(
    !VelocitySet<ZeroDimensional>,
    "ZeroDimensional should not satisfy VelocitySet concept"
);

static_assert(
    !VelocitySet<FourDimensional>,
    "FourDimensional should not satisfy VelocitySet concept"
);

static_assert(!VelocitySet<IntSize>, "IntSize should not satisfy VelocitySet concept");

static_assert(!VelocitySet<InvalidSize>, "InvalidSize should not satisfy VelocitySet concept");

static_assert(
    !VelocitySet<InvalidFloatingPointWeight>,
    "InvalidFloatingPointWeight should not satisfy VelocitySet concept"
);

TEST_CASE("Dummy test for VelocitySet concept")
{
    REQUIRE(true); // Ensures Catch2 runs this file
}
