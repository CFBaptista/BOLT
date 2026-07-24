#include "bolt/lbm/D1Q3.hpp"
#include "bolt/lbm/LatticeModel.hpp"

static_assert(bolt::lbm::LatticeModel<bolt::lbm::D1Q3<float>>);
static_assert(bolt::lbm::LatticeModel<bolt::lbm::D1Q3<double>>);
