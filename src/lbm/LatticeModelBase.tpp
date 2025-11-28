#include <cstddef>

#include "LatticeModelBase.hpp"

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::dimension() -> std::size_t
{
    return Derived::dimension_;
}

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::size() -> std::size_t
{
    return Derived::size_;
}

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::velocities() -> decltype(auto)
{
    return Derived::velocities_;
}

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::weights() -> decltype(auto)
{
    return Derived::weights_;
}
