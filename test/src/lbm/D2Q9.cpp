#include "bolt/lbm/D2Q9.hpp"
#include "bolt/core/concepts/LatticeModel.hpp"

static_assert(bolt::lbm::LatticeModel<bolt::lbm::D2Q9<float>>);
static_assert(bolt::lbm::LatticeModel<bolt::lbm::D2Q9<double>>);
