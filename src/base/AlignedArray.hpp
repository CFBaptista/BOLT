#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <mdspan>
#include <vector>

template <typename Real, std::size_t Alignment>
class AlignedAllocator
{
public:
    using value_type = Real;

    template <typename U>
    struct rebind
    {
        using other = AlignedAllocator<U, Alignment>;
    };

    AlignedAllocator() noexcept = default;

    template <typename U>
    constexpr explicit AlignedAllocator(const AlignedAllocator<U, Alignment>& other) noexcept;

    [[nodiscard]] static auto allocate(std::size_t count) -> Real*;

    static auto deallocate(Real* pointer, std::size_t element_count) noexcept -> void;
};

template <typename T1, std::size_t A1, typename T2, std::size_t A2>
constexpr auto
operator==(const AlignedAllocator<T1, A1>& left, const AlignedAllocator<T2, A2>& right) noexcept
    -> bool;

template <std::floating_point Real, std::size_t... Shape>
class AlignedArray
{
public:
    using value_type = Real;

    static constexpr std::size_t alignment = 64;
    static constexpr std::array<std::size_t, sizeof...(Shape)> shape = {Shape...};
    static constexpr std::size_t size = (Shape * ...);

    AlignedArray();
    ~AlignedArray() = default;
    AlignedArray(const AlignedArray&) = delete;
    auto operator=(const AlignedArray&) -> AlignedArray& = delete;
    AlignedArray(AlignedArray&&) noexcept = default;
    auto operator=(AlignedArray&&) noexcept -> AlignedArray& = default;

    auto operator[](std::size_t index) -> Real&;
    auto operator[](std::size_t index) const -> const Real&;

    template <typename... Indices>
    auto operator[](Indices... indices) -> Real&;

    template <typename... Indices>
    auto operator[](Indices... indices) const -> const Real&;

private:
    std::vector<Real, AlignedAllocator<Real, alignment>> data_;
    std::mdspan<Real, std::extents<std::size_t, Shape...>> view_;
};

#include "base/AlignedArray.tpp"
