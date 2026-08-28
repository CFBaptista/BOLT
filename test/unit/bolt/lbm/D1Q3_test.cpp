#include <catch2/catch_test_macros.hpp>

#include "bolt/lbm/D1Q3.hpp"
#include "bolt/lbm/LatticeModel.hpp"

SCENARIO("D1Q3 satisfies the LatticeModel concept for supported value types")
{
    STATIC_REQUIRE(bolt::lbm::LatticeModel<bolt::lbm::D1Q3<float>>);
    STATIC_REQUIRE(bolt::lbm::LatticeModel<bolt::lbm::D1Q3<double>>);
}
