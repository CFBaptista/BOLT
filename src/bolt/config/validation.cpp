#include "validation.hpp"

#include <filesystem>
#include <stdexcept>
#include <system_error>
#include <utility>

namespace bolt::config
{

FileValidator::FileValidator(std::filesystem::path file_path) : file_path_(std::move(file_path))
{
    if (file_path_.empty())
    {
        throw std::invalid_argument("File path cannot be empty.");
    }
}

auto FileValidator::value() const -> std::filesystem::path
{
    return file_path_;
}

auto FileValidator::exists() -> FileValidator&
{
    if (!std::filesystem::exists(file_path_))
    {
        throw std::runtime_error("File does not exist: " + file_path_.string());
    }

    return *this;
}

auto FileValidator::is_file() -> FileValidator&
{
    if (!std::filesystem::is_regular_file(file_path_))
    {
        throw std::runtime_error("Path is not a regular file: " + file_path_.string());
    }

    return *this;
}

auto FileValidator::readable() -> FileValidator&
{
    std::error_code error_code;

    auto permissions = std::filesystem::status(file_path_, error_code).permissions();
    if (error_code ||
        (permissions & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
    {
        throw std::runtime_error("File is not readable: " + file_path_.string());
    }

    return *this;
}

auto FileValidator::writable() -> FileValidator&
{
    std::error_code error_code;

    auto permissions = std::filesystem::status(file_path_, error_code).permissions();
    if (error_code ||
        (permissions & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
    {
        throw std::runtime_error("File is not writable: " + file_path_.string());
    }

    return *this;
}

DirectoryValidator::DirectoryValidator(std::filesystem::path directory_path)
    : directory_path_(std::move(directory_path))
{
    if (directory_path_.empty())
    {
        throw std::invalid_argument("Directory path cannot be empty.");
    }
}

auto DirectoryValidator::value() const -> std::filesystem::path
{
    return directory_path_;
}

auto DirectoryValidator::exists() -> DirectoryValidator&
{
    if (!std::filesystem::exists(directory_path_))
    {
        throw std::runtime_error("Directory does not exist: " + directory_path_.string());
    }

    return *this;
}

auto DirectoryValidator::is_directory() -> DirectoryValidator&
{
    if (!std::filesystem::is_directory(directory_path_))
    {
        throw std::runtime_error("Path is not a directory: " + directory_path_.string());
    }

    return *this;
}

auto DirectoryValidator::readable() -> DirectoryValidator&
{
    std::error_code error_code;

    auto permissions = std::filesystem::status(directory_path_, error_code).permissions();
    if (error_code ||
        (permissions & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
    {
        throw std::runtime_error("Directory is not readable: " + directory_path_.string());
    }

    return *this;
}

auto DirectoryValidator::writable() -> DirectoryValidator&
{
    std::error_code error_code;

    auto permissions = std::filesystem::status(directory_path_, error_code).permissions();
    if (error_code ||
        (permissions & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
    {
        throw std::runtime_error("Directory is not writable: " + directory_path_.string());
    }

    return *this;
}

} // namespace bolt::config
