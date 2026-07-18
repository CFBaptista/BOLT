#include "lbm/D2Q9.hpp"
#include "core/concepts/LatticeModel.hpp"

static_assert(bolt::lbm::LatticeModel<bolt::lbm::D2Q9<float>>);
static_assert(bolt::lbm::LatticeModel<bolt::lbm::D2Q9<double>>);
