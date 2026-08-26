#include <catch2/catch_test_macros.hpp>

#include "bolt/lbm/D2Q9.hpp"
#include "bolt/lbm/LatticeModel.hpp"

SCENARIO("D2Q9 satisfies the LatticeModel concept for supported value types")
{
    STATIC_REQUIRE(bolt::lbm::LatticeModel<bolt::lbm::D2Q9<float>>);
    STATIC_REQUIRE(bolt::lbm::LatticeModel<bolt::lbm::D2Q9<double>>);
}
