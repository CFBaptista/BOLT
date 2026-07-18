#pragma once

#include <concepts>
#include <cstddef>
#include <new>

#include "core/containers/AlignedArray.hpp" // NOLINT(misc-header-include-cycle)

namespace bolt
{

namespace core
{

template <typename Real, std::size_t Alignment>
template <typename U>
constexpr AlignedAllocator<Real, Alignment>::AlignedAllocator(
    const AlignedAllocator<U, Alignment>& other
) noexcept
{
    (void)other;
}

template <typename Real, std::size_t Alignment>
// cppcheck-suppress unusedFunction
auto AlignedAllocator<Real, Alignment>::allocate(std::size_t count) -> Real*
{
    if (count > std::size_t(-1) / sizeof(Real))
    {
        throw std::bad_array_new_length{};
    }

    auto* pointer = ::operator new[](count * sizeof(Real), std::align_val_t{Alignment});
    return static_cast<Real*>(pointer);
}

template <typename Real, std::size_t Alignment>
// cppcheck-suppress unusedFunction
auto AlignedAllocator<Real, Alignment>::deallocate(
    Real* pointer,
    std::size_t element_count
) noexcept -> void
{
    (void)element_count;
    ::operator delete[](pointer, std::align_val_t{Alignment});
}

template <typename T1, std::size_t A1, typename T2, std::size_t A2>
constexpr auto
operator==(const AlignedAllocator<T1, A1>& left, const AlignedAllocator<T2, A2>& right) noexcept
    -> bool
{
    (void)left;
    (void)right;
    return A1 == A2;
}

template <std::floating_point Real, std::size_t... Shape>
AlignedArray<Real, Shape...>::AlignedArray() : data_(size), view_(data_.data(), shape)
{
}

template <std::floating_point Real, std::size_t... Shape>
auto AlignedArray<Real, Shape...>::operator[](std::size_t index) -> Real&
{
    return data_[index];
}

template <std::floating_point Real, std::size_t... Shape>
auto AlignedArray<Real, Shape...>::operator[](std::size_t index) const -> const Real&
{
    return data_[index];
}

template <std::floating_point Real, std::size_t... Shape>
template <typename... Indices>
auto AlignedArray<Real, Shape...>::operator[](Indices... indices) -> Real&
{
    return view_[indices...];
}

template <std::floating_point Real, std::size_t... Shape>
template <typename... Indices>
auto AlignedArray<Real, Shape...>::operator[](Indices... indices) const -> const Real&
{
    return view_[indices...];
}

} // namespace core

} // namespace bolt
