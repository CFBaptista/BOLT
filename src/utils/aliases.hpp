#pragma once

#include <array>
#include <cstddef>

using Count = std::size_t;

using Index = int;

template <typename Type, std::size_t Size>
using Vector = std::array<Type, Size>;

template <typename Type, std::size_t Rows, std::size_t Cols>
using Matrix = std::array<std::array<Type, Cols>, Rows>;
