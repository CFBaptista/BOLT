#pragma once

#include <type_traits>

/**
 * @class CollisionOperatorBase
 *
 * @brief Base class for collision operators at lattice nodes.
 */
class CollisionOperatorBase
{
};

/**
 * @concept CollisionOperator
 *
 * @brief Concept used for constraining the template parameter of consumers of collision operators.
 *
 * @details This concept checks if the type `Derived` is derived from the `CollisionOperatorBase`
 * class.
 *
 * @tparam Derived The type to be checked.
 */
template <typename Derived>
concept CollisionOperator = requires { std::is_base_of_v<CollisionOperatorBase, Derived>; };
