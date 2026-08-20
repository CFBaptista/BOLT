#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <mdspan>
#include <vector>

#include "aligned_allocator.hpp"

namespace bolt
{

/// @brief A class template representing an array of elements with a specified alignment.
///
/// @tparam Real The type of elements in the array.
/// @tparam Shape The dimensions of the array.
template <std::floating_point Real, std::size_t... Shape>
class array
{
public:
    /// @brief The type of elements in the array.
    using value_type = Real;

    /// @brief The alignment of the array in bytes.
    static constexpr std::size_t alignment = 64;
    /// @brief The shape of the array, i.e., the number of elements in each dimension.
    static constexpr std::array<std::size_t, sizeof...(Shape)> shape = {Shape...};
    /// @brief The total number of elements in the array.
    static constexpr std::size_t size = (Shape * ...);

    /// @brief Default constructor.
    array();

    /// @brief Destructor.
    ~array() = default;

    array(const array&) = delete;
    auto operator=(const array&) -> array& = delete;

    /// @brief Move constructor.
    array(array&&) noexcept = default;

    /// @brief Move assignment operator.
    ///
    /// @return A reference to the assigned object.
    auto operator=(array&&) noexcept -> array& = default;

    /// @brief Access an element by its linear index.
    ///
    /// @param index The linear index of the element.
    ///
    /// @return A reference to the element at the specified index.
    auto operator[](std::size_t index) -> Real&;

    /// @brief Access an element by its linear index (const version).
    ///
    /// @param index The linear index of the element.
    ///
    /// @return A const reference to the element at the specified index.
    auto operator[](std::size_t index) const -> const Real&;

    /// @brief Access an element by its multi-dimensional indices.
    ///
    /// @param indices The multi-dimensional indices of the element.
    ///
    /// @return A reference to the element at the specified indices.
    template <typename... Indices>
    auto operator[](Indices... indices) -> Real&;

    /// @brief Access an element by its multi-dimensional indices (const version).
    ///
    /// @param indices The multi-dimensional indices of the element.
    ///
    /// @return A const reference to the element at the specified indices.
    template <typename... Indices>
    auto operator[](Indices... indices) const -> const Real&;

private:
    std::vector<Real, aligned_allocator<Real, alignment>> data_;
    std::mdspan<Real, std::extents<std::size_t, Shape...>> view_;
};

} // namespace bolt

#include "array.tpp"
