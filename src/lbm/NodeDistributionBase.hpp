#pragma once

#include <type_traits>

/**
 * @class NodeDistributionBase
 *
 * @brief Class that serves as a base for distribution functions at lattice nodes.
 */
class NodeDistributionBase
{
};

/**
 * @concept NodeDistribution
 *
 * @brief Concept used for constraining the template parameter of consumers of node distributions.
 *
 * @details This concept checks if the type `Derived` is derived from the `NodeDistributionBase`
 * class.
 *
 * @tparam Derived The type to be checked.
 */
template <typename Derived>
concept NodeDistribution = requires { std::is_base_of_v<NodeDistributionBase, Derived>; };
