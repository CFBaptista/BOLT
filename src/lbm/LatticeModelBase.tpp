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
constexpr auto LatticeModelBase<Derived>::velocities()
{
    return Derived::velocities_;
}

template <typename Derived>
constexpr auto LatticeModelBase<Derived>::weights()
{
    return Derived::weights_;
}
