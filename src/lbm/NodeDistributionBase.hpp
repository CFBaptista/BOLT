#pragma once

#include <type_traits>

class NodeDistributionBase
{
};

template <typename Derived>
concept NodeDistribution = requires { std::is_base_of_v<NodeDistributionBase, Derived>; };
