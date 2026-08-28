#include <catch2/catch_test_macros.hpp>

#include "bolt/lbm/D3Q27.hpp"
#include "bolt/lbm/LatticeModel.hpp"

SCENARIO("D3Q27 satisfies the LatticeModel concept for supported value types")
{
    STATIC_REQUIRE(bolt::lbm::LatticeModel<bolt::lbm::D3Q27<float>>);
    STATIC_REQUIRE(bolt::lbm::LatticeModel<bolt::lbm::D3Q27<double>>);
}
