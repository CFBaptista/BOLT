#include "lbm/D3Q27.hpp"
#include "lbm/LatticeModel.hpp"

static_assert(bolt::lbm::LatticeModel<bolt::lbm::D3Q27<float>>);
static_assert(bolt::lbm::LatticeModel<bolt::lbm::D3Q27<double>>);
