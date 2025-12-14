#pragma once

#include "lbm/CollisionOperatorBase.hpp"
#include "lbm/DensityDistribution.hpp"
#include "lbm/EquilibriumDistributionBase.hpp"
#include "lbm/VelocitySetBase.hpp"

template <VelocitySet Velocity, EquilibriumDistribution Equilibrium>
class BhatnagarGrossKrook : public CollisionOperatorBase
{
public:
    /// The velocity set type.
    using VelocityType = Velocity;
    /// The equilibrium distribution type.
    using EquilibriumType = Equilibrium;
    /// The floating-point type.
    using Float = typename Velocity::Float;

    BhatnagarGrossKrook(const Float& timeStep, const Float& relaxationTime);

    auto collide(const DensityDistribution<Velocity>& distribution
    ) const -> DensityDistribution<Velocity>;

private:
    Float timeStep_;
    Float relaxationTime_;
    Float relaxationFactor_;
    Float oneMinusRelaxationFactor_;
};

#include "lbm/BhatnagarGrossKrook.tpp"
