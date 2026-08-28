#pragma once

#include <filesystem>

#include "bolt/core/Number.hpp"

namespace bolt::config
{

/// @brief Validates a file path by checking its existence, type, and permissions.
///
/// Provides an interface for validating file paths by means of chaining operations. Supports common
/// validation checks such as existence, proper typing, and read/write permissions.
class FileValidator
{
public:
    /// @brief Constructs a file validator for the given file path.
    ///
    /// @param file_path Path to the file to validate.
    ///
    /// @throws std::invalid_argument if the file path is empty.
    explicit FileValidator(std::filesystem::path file_path);

    /// @brief Gets the stored file path.
    ///
    /// @return File path as a `std::filesystem::path`.
    auto value() const -> std::filesystem::path;

    /// @brief Checks whether the file exists.
    ///
    /// @return Reference to the current `FileValidator` instance for method chaining.
    auto exists() -> FileValidator&;

    /// @brief Checks whether the path points to a regular file.
    ///
    /// @return Reference to the current `FileValidator` instance for method chaining.
    auto is_file() -> FileValidator&;

    /// @brief Checks whether the file is readable.
    ///
    /// @return Reference to the current `FileValidator` instance for method chaining.
    auto readable() -> FileValidator&;

    /// @brief Checks whether the file is writable.
    ///
    /// @return Reference to the current `FileValidator` instance for method chaining.
    auto writable() -> FileValidator&;

private:
    std::filesystem::path file_path_;
};

/// @brief Validates a directory path by checking its existence, type, and permissions.
///
/// Provides an interface for validating directory paths by means of chaining operations. Supports
/// common validation checks such as existence, proper typing, and read/write permissions.
class DirectoryValidator
{
public:
    /// @brief Constructs a directory validator for the given directory path.
    ///
    /// @param directory_path Path to the directory to validate.
    ///
    /// @throws std::invalid_argument if the directory path is empty.
    explicit DirectoryValidator(std::filesystem::path directory_path);

    /// @brief Gets the stored directory path.
    ///
    /// @return Directory path as a `std::filesystem::path`.
    auto value() const -> std::filesystem::path;

    /// @brief Checks whether the directory exists.
    ///
    /// @return Reference to the current `DirectoryValidator` instance for method chaining.
    auto exists() -> DirectoryValidator&;

    /// @brief Checks whether the path points to a directory.
    ///
    /// @return Reference to the current `DirectoryValidator` instance for method chaining.
    auto is_directory() -> DirectoryValidator&;

    /// @brief Checks whether the directory is readable.
    ///
    /// @return Reference to the current `DirectoryValidator` instance for method chaining.
    auto readable() -> DirectoryValidator&;

    /// @brief Checks whether the directory is writable.
    ///
    /// @return Reference to the current `DirectoryValidator` instance for method chaining.
    auto writable() -> DirectoryValidator&;

private:
    std::filesystem::path directory_path_;
};

/// @brief Stores a value of type `T` and provides methods to validate it.
///
/// Provides an interface for validating numerical values by means of chaining operations. Supports
/// common validation checks such as existence, proper typing, and bounds checking.
///
/// @tparam T Type of the value to validate.
template <Number T>
class NumberValidator
{
public:
    /// @brief Constructs a number validator for a value of type `T`.
    ///
    /// @param value Value to validate.
    ///
    /// @throws std::invalid_argument if the value is not of type `T`.
    explicit NumberValidator(const T& value);

    /// @brief Gets the stored value.
    ///
    /// @return Value of type `T`.
    auto value() const -> T;

    /// @brief Ensures the value is greater than the given reference.
    ///
    /// @param reference Value to compare against.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not greater than the reference.
    auto greater_than(const T& reference) -> NumberValidator&;

    /// @brief Ensures the value is greater than or equal to the given reference.
    ///
    /// @param reference Value to compare against.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not greater than or equal to the reference.
    auto greater_or_equal(const T& reference) -> NumberValidator&;

    /// @brief Ensures the value is less than the given reference.
    ///
    /// @param reference Value to compare against.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not less than the reference.
    auto less_than(const T& reference) -> NumberValidator&;

    /// @brief Ensures the value is less than or equal to the given reference.
    ///
    /// @param reference Value to compare against.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not less than or equal to the reference.
    auto less_or_equal(const T& reference) -> NumberValidator&;

    /// @brief Ensures the value is between the given lower and upper bounds (inclusive).
    ///
    /// @param lower Lower bound.
    /// @param upper Upper bound.
    ///
    /// @return NumberValidator instance for method chaining.
    ///
    /// @throws std::invalid_argument if the value is not between the lower and upper bounds
    /// (inclusive).
    auto between(const T& lower, const T& upper) -> NumberValidator&;

private:
    T value_;
};

} // namespace bolt::config

#include "validation.tpp"
