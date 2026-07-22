#pragma once

#include <cstddef>

namespace bolt
{

/// @brief A custom allocator that aligns memory allocations to a specified alignment.
///
/// @tparam Real The type of elements to allocate.
/// @tparam Alignment The alignment in bytes.
template <typename Real, std::size_t Alignment>
class aligned_allocator
{
public:
    /// @brief The type of elements allocated by the allocator.
    using value_type = Real;

    /// @brief A nested template struct to rebind the allocator to a different type.
    ///
    /// @tparam U The new type to which the allocator will be rebound.
    template <typename U>
    struct rebind
    {
        /// @brief The type of the rebound allocator.
        using other = aligned_allocator<U, Alignment>;
    };

    aligned_allocator() noexcept = default;

    /// @brief Constructs an allocator from another allocator of a different type.
    ///
    /// @tparam U The type of the other allocator.
    ///
    /// @param other The other allocator.
    template <typename U>
    constexpr explicit aligned_allocator(const aligned_allocator<U, Alignment>& other) noexcept;

    /// @brief Allocates memory for a specified number of elements.
    ///
    /// @param count The number of elements to allocate.
    ///
    /// @return A pointer to the allocated memory.
    [[nodiscard]] static auto allocate(std::size_t count) -> Real*;

    /// @brief Deallocates memory previously allocated by the allocator.
    ///
    /// @param pointer A pointer to the memory to deallocate.
    /// @param element_count The number of elements to deallocate.
    static auto deallocate(Real* pointer, std::size_t element_count) noexcept -> void;
};

/// @brief Compares two aligned allocators for equality.
///
/// @tparam T1 The type of elements in the first allocator.
/// @tparam A1 The alignment of the first allocator.
/// @tparam T2 The type of elements in the second allocator.
/// @tparam A2 The alignment of the second allocator.
///
/// @param left The first allocator.
/// @param right The second allocator.
///
/// @return True if the allocators are equal, false otherwise.
template <typename T1, std::size_t A1, typename T2, std::size_t A2>
constexpr auto
operator==(const aligned_allocator<T1, A1>& left, const aligned_allocator<T2, A2>& right) noexcept
    -> bool;

} // namespace bolt

#include "aligned_allocator.tpp"
