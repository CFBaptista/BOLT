#include <catch2/catch_test_macros.hpp>

#include "lbm/VelocitySetBase.hpp"

class ValidVelocitySet : public VelocitySetBase<ValidVelocitySet>
{
public:
    using Float = Real;

    friend class VelocitySetBase<ValidVelocitySet>;

    static constexpr Count dimension_{2};

    static constexpr Count size_{7};

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{4};
};

class NoBase
{
public:
    using Float = Real;

    friend class VelocitySetBase<NoBase>;

    static constexpr Count dimension_ = 2;

    static constexpr Count size_ = 7;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{4};
};

class InvalidValueType : public VelocitySetBase<InvalidValueType>
{
public:
    using Float = Index;

    friend class VelocitySetBase<InvalidValueType>;

    static constexpr Count dimension_ = 2;

    static constexpr Count size_ = 7;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{4};
};

class ZeroDimensional : public VelocitySetBase<ZeroDimensional>
{
public:
    using Float = Real;

    friend class VelocitySetBase<ZeroDimensional>;

    static constexpr Count dimension_ = 0;

    static constexpr Count size_ = 7;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{4};
};

class FourDimensional : public VelocitySetBase<FourDimensional>
{
public:
    using Float = Real;

    friend class VelocitySetBase<FourDimensional>;

    static constexpr Count dimension_ = 4;

    static constexpr Count size_ = 7;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{4};
};

class IntSize : public VelocitySetBase<IntSize>
{
public:
    using Float = Real;

    friend class VelocitySetBase<IntSize>;

    static constexpr Count dimension_ = 2;

    static constexpr Index size_ = 0;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{4};
};

class InvalidSize : public VelocitySetBase<InvalidSize>
{
public:
    using Float = Real;

    friend class VelocitySetBase<InvalidSize>;

    static constexpr Count dimension_ = 2;

    static constexpr Count size_ = 0;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{4};
};

class InvalidFloatingPointWeight : public VelocitySetBase<InvalidFloatingPointWeight>
{
public:
    using Float = char;

    friend class VelocitySetBase<InvalidFloatingPointWeight>;

    static constexpr Count dimension_ = 2;

    static constexpr Count size_ = 7;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{4};
};

class IntSoundSpeed : public VelocitySetBase<IntSoundSpeed>
{
public:
    using Float = Real;

    friend class VelocitySetBase<IntSoundSpeed>;

    static constexpr Count dimension_ = 2;

    static constexpr Count size_ = 7;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Index soundSpeedInverseSquared_{3};
};

class NegativeSoundSpeed : public VelocitySetBase<NegativeSoundSpeed>
{
public:
    using Float = Real;

    friend class VelocitySetBase<NegativeSoundSpeed>;

    static constexpr Count dimension_ = 2;

    static constexpr Count size_ = 7;

    static constexpr Matrix<Index, size_, dimension_> velocities_{};

    static constexpr Vector<Float, size_> weights_{};

    static constexpr Float soundSpeedInverseSquared_{-3};
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

static_assert(
    !VelocitySet<NegativeSoundSpeed>,
    "NegativeSoundSpeed should not satisfy VelocitySet concept"
);

static_assert(!VelocitySet<IntSoundSpeed>, "IntSoundSpeed should not satisfy VelocitySet concept");

TEST_CASE("Dummy test for VelocitySet concept")
{
    REQUIRE(true); // Ensures Catch2 runs this file
}
