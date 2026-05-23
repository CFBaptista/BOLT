#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <mdspan>
#include <vector>

/**
 * @brief A custom allocator that aligns memory allocations to a specified alignment.
 *
 * @tparam Real The type of elements to allocate.
 * @tparam Alignment The alignment in bytes.
 */
template <typename Real, std::size_t Alignment>
class AlignedAllocator
{
public:
    /**
     * @brief The type of elements allocated by the allocator.
     */
    using value_type = Real;

    /**
     * @brief A nested template struct to rebind the allocator to a different type.
     *
     * @tparam U The new type to which the allocator will be rebound.
     */
    template <typename U>
    struct rebind
    {
        /**
         * @brief The type of the rebound allocator.
         */
        using other = AlignedAllocator<U, Alignment>;
    };

    AlignedAllocator() noexcept = default;

    /**
     * @brief Constructs an allocator from another allocator of a different type.
     *
     * @tparam U The type of the other allocator.
     * @param other The other allocator.
     */
    template <typename U>
    constexpr explicit AlignedAllocator(const AlignedAllocator<U, Alignment>& other) noexcept;

    /**
     * @brief Allocates memory for a specified number of elements.
     *
     * @param count The number of elements to allocate.
     * @return A pointer to the allocated memory.
     */
    [[nodiscard]] static auto allocate(std::size_t count) -> Real*;

    /**
     * @brief Deallocates memory previously allocated by the allocator.
     *
     * @param pointer A pointer to the memory to deallocate.
     * @param element_count The number of elements to deallocate.
     */
    static auto deallocate(Real* pointer, std::size_t element_count) noexcept -> void;
};

template <typename T1, std::size_t A1, typename T2, std::size_t A2>
constexpr auto
operator==(const AlignedAllocator<T1, A1>& left, const AlignedAllocator<T2, A2>& right) noexcept
    -> bool;

/**
 * @brief A class template representing an array of elements with a specified alignment.
 *
 * @tparam Real The type of elements in the array.
 * @tparam Shape The dimensions of the array.
 */
template <std::floating_point Real, std::size_t... Shape>
class AlignedArray
{
public:
    /**
     * @brief The type of elements in the array.
     */
    using value_type = Real;

    /**
     * @brief The alignment of the array in bytes.
     */
    static constexpr std::size_t alignment = 64;
    /**
     * @brief The shape of the array, i.e., the number of elements in each dimension.
     */
    static constexpr std::array<std::size_t, sizeof...(Shape)> shape = {Shape...};
    /**
     * @brief The total number of elements in the array.
     */
    static constexpr std::size_t size = (Shape * ...);

    /**
     * @brief Default constructor.
     */
    AlignedArray();
    /**
     * @brief Destructor.
     */
    ~AlignedArray() = default;
    AlignedArray(const AlignedArray&) = delete;
    auto operator=(const AlignedArray&) -> AlignedArray& = delete;
    /**
     * @brief Move constructor.
     */
    AlignedArray(AlignedArray&&) noexcept = default;
    /**
     * @brief Move assignment operator.
     */
    auto operator=(AlignedArray&&) noexcept -> AlignedArray& = default;

    /**
     * @brief Access an element by its linear index.
     *
     * @param index The linear index of the element.
     * @return A reference to the element at the specified index.
     */
    auto operator[](std::size_t index) -> Real&;
    /**
     * @brief Access an element by its linear index (const version).
     *
     * @param index The linear index of the element.
     * @return A const reference to the element at the specified index.
     */
    auto operator[](std::size_t index) const -> const Real&;

    /**
     * @brief Access an element by its multi-dimensional indices.
     *
     * @param indices The multi-dimensional indices of the element.
     * @return A reference to the element at the specified indices.
     */
    template <typename... Indices>
    auto operator[](Indices... indices) -> Real&;

    /**
     * @brief Access an element by its multi-dimensional indices (const version).
     *
     * @param indices The multi-dimensional indices of the element.
     * @return A const reference to the element at the specified indices.
     */
    template <typename... Indices>
    auto operator[](Indices... indices) const -> const Real&;

private:
    std::vector<Real, AlignedAllocator<Real, alignment>> data_;
    std::mdspan<Real, std::extents<std::size_t, Shape...>> view_;
};

#include "base/AlignedArray.tpp"
