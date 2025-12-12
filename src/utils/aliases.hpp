#pragma once

#include <array>
#include <concepts>
#include <cstddef>

using Count = std::size_t;

using Index = int;

#ifndef REAL_TYPE
#define REAL_TYPE double
#endif

using Real = REAL_TYPE;

static_assert(std::floating_point<Real>, "Real must be a floating-point type");

template <typename Type, std::size_t Size>
using Vector = std::array<Type, Size>;

template <typename Type, std::size_t Rows, std::size_t Cols>
using Matrix = std::array<std::array<Type, Cols>, Rows>;
