#pragma once

#include "lbm/CollisionOperatorBase.hpp"
#include "lbm/DensityDistribution.hpp"
#include "lbm/EquilibriumDistributionBase.hpp"
#include "lbm/VelocitySetBase.hpp"

template <VelocitySet Set, EquilibriumDistribution Equilibrium>
class BhatnagarGrossKrook : public CollisionOperatorBase
{
public:
    using Real = typename Set::Real;

    BhatnagarGrossKrook(const Real& timeStep, const Real& relaxationTime);

    auto collide(const DensityDistribution<Set>& distribution) const -> DensityDistribution<Set>;

private:
    Real timeStep_;
    Real relaxationTime_;
    Real relaxationFactor_;
    Real oneMinusRelaxationFactor_;
};

#include "lbm/BhatnagarGrossKrook.tpp"
