#include <cstddef>

#include "LatticeModelBase.hpp"

template <typename Derived, std::floating_point Real, std::size_t Dimension, std::size_t Size>
constexpr auto LatticeModelBase<Derived, Real, Dimension, Size>::dimension() -> std::size_t
{
    return Dimension;
}

template <typename Derived, std::floating_point Real, std::size_t Dimension, std::size_t Size>
constexpr auto LatticeModelBase<Derived, Real, Dimension, Size>::size() -> std::size_t
{
    return Size;
}

template <typename Derived, std::floating_point Real, std::size_t Dimension, std::size_t Size>
constexpr auto LatticeModelBase<Derived, Real, Dimension, Size>::velocities()
    -> std::array<std::array<int, Dimension>, Size>
{
    return Derived::velocities_;
}

template <typename Derived, std::floating_point Real, std::size_t Dimension, std::size_t Size>
constexpr auto LatticeModelBase<Derived, Real, Dimension, Size>::weights() -> std::array<Real, Size>
{
    return Derived::weights_;
}
