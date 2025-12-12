#pragma once

#include "lbm/CollisionOperatorBase.hpp"
#include "lbm/DensityDistribution.hpp"
#include "lbm/EquilibriumDistributionBase.hpp"
#include "lbm/VelocitySetBase.hpp"

template <VelocitySet Set, EquilibriumDistribution Equilibrium>
class BhatnagarGrossKrook : public CollisionOperatorBase
{
public:
    using Float = typename Set::Float;

    BhatnagarGrossKrook(const Float& timeStep, const Float& relaxationTime);

    auto collide(const DensityDistribution<Set>& distribution) const -> DensityDistribution<Set>;

private:
    Float timeStep_;
    Float relaxationTime_;
    Float relaxationFactor_;
    Float oneMinusRelaxationFactor_;
};

#include "lbm/BhatnagarGrossKrook.tpp"
