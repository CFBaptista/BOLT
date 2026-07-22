#pragma once

#include <cstddef>
#include <new>

#include "aligned_allocator.hpp" // NOLINT(misc-header-include-cycle)

namespace bolt::core
{

template <typename Real, std::size_t Alignment>
template <typename U>
constexpr aligned_allocator<Real, Alignment>::aligned_allocator(
    const aligned_allocator<U, Alignment>& other
) noexcept
{
    (void)other;
}

template <typename Real, std::size_t Alignment>
// cppcheck-suppress unusedFunction
auto aligned_allocator<Real, Alignment>::allocate(std::size_t count) -> Real*
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
auto aligned_allocator<Real, Alignment>::deallocate(
    Real* pointer,
    std::size_t element_count
) noexcept -> void
{
    (void)element_count;
    ::operator delete[](pointer, std::align_val_t{Alignment});
}

template <typename T1, std::size_t A1, typename T2, std::size_t A2>
constexpr auto
operator==(const aligned_allocator<T1, A1>& left, const aligned_allocator<T2, A2>& right) noexcept
    -> bool
{
    (void)left;
    (void)right;
    return A1 == A2;
}

} // namespace bolt::core
