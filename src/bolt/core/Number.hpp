#pragma once

#include <type_traits>

namespace bolt

{

/// @brief Checks if a type is a number (arithmetic type excluding bool).
template <typename T>
concept Number = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

} // namespace bolt
