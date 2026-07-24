#include <array>
#include <cstddef>

#include "bolt/lbm/LatticeModel.hpp"

template <typename Real, std::size_t Size>
consteval auto filled_weights(Real value) -> std::array<Real, Size>
{
    std::array<Real, Size> weights{};
    weights.fill(value);
    return weights;
}

template <std::size_t Dimension, std::size_t Size>
consteval auto zero_velocities() -> std::array<std::array<int, Dimension>, Size>
{
    return {};
}

template <typename Real>
class ValidLattice
{
public:
    using value_type = Real;
    static constexpr std::size_t dimension = 2;
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
    static constexpr std::array<value_type, size> weights{
        value_type{4} / value_type{9},  value_type{1} / value_type{9},
        value_type{1} / value_type{9},  value_type{1} / value_type{9},
        value_type{1} / value_type{9},  value_type{1} / value_type{36},
        value_type{1} / value_type{36}, value_type{1} / value_type{36},
        value_type{1} / value_type{36}
    };
    static constexpr value_type sound_speed_inverse_squared{value_type{3}};
};

class NonFloatingValueTypeLattice
{
public:
    using value_type = int;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 9;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr auto weights = filled_weights<value_type, size>(value_type{0});
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3};
};

class WrongDimensionTypeLattice
{
public:
    using value_type = double;
    static constexpr unsigned dimension = 2;
    static constexpr std::size_t size = 9;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr auto weights = filled_weights<value_type, size>(value_type{0});
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class ZeroDimensionLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 0;
    static constexpr std::size_t size = 1;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr auto weights = filled_weights<value_type, size>(value_type{1});
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class OversizedDimensionLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 4;
    static constexpr std::size_t size = 1;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr auto weights = filled_weights<value_type, size>(value_type{1});
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class WrongSizeTypeLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr unsigned size = 9;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr auto weights = filled_weights<value_type, size>(value_type{0});
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class ZeroSizeLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 0;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr auto weights = filled_weights<value_type, size>(value_type{0});
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class WrongVelocitiesTypeLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 9;
    // cppcheck-suppress unusedStructMember
    static constexpr std::array<std::array<short, dimension>, size> velocities{};
    // cppcheck-suppress unusedStructMember
    static constexpr auto weights = filled_weights<value_type, size>(value_type{0});
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class NonZeroVelocitySumLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 2;
    // cppcheck-suppress unusedStructMember
    static constexpr std::array<std::array<int, dimension>, size> velocities{{{{1, 0}}, {{0, 0}}}};
    // cppcheck-suppress unusedStructMember
    static constexpr std::array<value_type, size> weights{value_type{0.5}, value_type{0.5}};
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class WrongWeightsTypeLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 9;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr std::array<float, size> weights{};
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class NonUnitWeightSumLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 2;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr std::array<value_type, size> weights{value_type{0.25}, value_type{0.25}};
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{3.0};
};

class WrongSoundSpeedTypeLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 9;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr auto weights = filled_weights<value_type, size>(value_type{0});
    // cppcheck-suppress unusedStructMember
    static constexpr float sound_speed_inverse_squared{3.0F};
};

class ZeroSoundSpeedLattice
{
public:
    using value_type = double;
    static constexpr std::size_t dimension = 2;
    static constexpr std::size_t size = 1;
    // cppcheck-suppress unusedStructMember
    static constexpr auto velocities = zero_velocities<dimension, size>();
    // cppcheck-suppress unusedStructMember
    static constexpr std::array<value_type, size> weights{value_type{1}};
    // cppcheck-suppress unusedStructMember
    static constexpr value_type sound_speed_inverse_squared{0.0};
};

static_assert(bolt::lbm::LatticeModel<ValidLattice<float>>);
static_assert(bolt::lbm::LatticeModel<ValidLattice<double>>);
static_assert(!bolt::lbm::LatticeModel<NonFloatingValueTypeLattice>);
static_assert(!bolt::lbm::LatticeModel<WrongDimensionTypeLattice>);
static_assert(!bolt::lbm::LatticeModel<ZeroDimensionLattice>);
static_assert(!bolt::lbm::LatticeModel<OversizedDimensionLattice>);
static_assert(!bolt::lbm::LatticeModel<WrongSizeTypeLattice>);
static_assert(!bolt::lbm::LatticeModel<ZeroSizeLattice>);
static_assert(!bolt::lbm::LatticeModel<WrongVelocitiesTypeLattice>);
static_assert(!bolt::lbm::LatticeModel<NonZeroVelocitySumLattice>);
static_assert(!bolt::lbm::LatticeModel<WrongWeightsTypeLattice>);
static_assert(!bolt::lbm::LatticeModel<NonUnitWeightSumLattice>);
static_assert(!bolt::lbm::LatticeModel<WrongSoundSpeedTypeLattice>);
static_assert(!bolt::lbm::LatticeModel<ZeroSoundSpeedLattice>);
