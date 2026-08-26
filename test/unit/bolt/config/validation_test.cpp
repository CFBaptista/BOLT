#include <filesystem>
#include <fstream>
#include <stdexcept>

#include <catch2/catch_test_macros.hpp>

#include "bolt/config/validation.hpp"

SCENARIO("NumberValidator accepts values that satisfy the requested bounds")
{
    GIVEN("A validator for a value")
    {
        const int value = 5;
        const int lower_bound = 3;
        const int upper_bound = 7;

        bolt::config::NumberValidator<int> validator{value};

        WHEN("It is checked to be greater than a smaller value")
        {
            const auto& result = validator.greater_than(lower_bound);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be greater than or equal to a smaller value")
        {
            const auto& result = validator.greater_or_equal(lower_bound);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be greater than or equal to its own value")
        {
            const auto& result = validator.greater_or_equal(value);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be less than a greater value")
        {
            const auto& result = validator.less_than(upper_bound);

            THEN("the validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be lesser than or equal to a greater value")
        {
            const auto& result = validator.less_or_equal(upper_bound);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be lesser than or equal to its own value")
        {
            const auto& result = validator.less_or_equal(value);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }

        WHEN("It is checked to be between the lower and upper bounds")
        {
            const auto& result = validator.between(lower_bound, upper_bound);

            THEN("The validator remains usable and preserves the original value")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == value);
            }
        }
    }
}

SCENARIO("NumberValidator rejects values that violate the requested bounds")
{
    GIVEN("A validator for a value")
    {
        const int value = 5;
        const int less_than_lower_bound = 3;
        const int less_than_upper_bound = 4;
        const int greater_than_lower_bound = 6;
        const int greater_than_upper_bound = 10;

        bolt::config::NumberValidator<int> validator{value};

        WHEN("It is checked to be greater than its own value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.greater_than(value), std::invalid_argument);
            }
        }

        WHEN("It is checked to be greater than or equal to a greater value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    validator.greater_or_equal(greater_than_lower_bound), std::invalid_argument
                );
            }
        }

        WHEN("It is checked to be less than its own value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.less_than(value), std::invalid_argument);
            }
        }

        WHEN("It is checked to be less than or equal to a smaller value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    validator.less_or_equal(less_than_upper_bound), std::invalid_argument
                );
            }
        }

        WHEN("It is checked to be between bounds that are both greater than its own value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    validator.between(greater_than_lower_bound, greater_than_upper_bound),
                    std::invalid_argument
                );
            }
        }

        WHEN("It is checked to be between bounds that are both less than its own value")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    validator.between(less_than_lower_bound, less_than_upper_bound),
                    std::invalid_argument
                );
            }
        }
    }
}

SCENARIO("FileValidator accepts a valid path on construction")
{
    GIVEN("A non-empty file path")
    {
        const std::filesystem::path file_path =
            std::filesystem::path{BOLT_TEST_DATA_DIRECTORY} / "configuration.toml";

        WHEN("A FileValidator is constructed with it")
        {
            const bolt::config::FileValidator validator{file_path};

            THEN("The validator stores and returns the path")
            {
                REQUIRE(validator.value() == file_path);
            }
        }
    }
}

SCENARIO("FileValidator rejects an empty path on construction")
{
    GIVEN("An empty path")
    {
        const std::filesystem::path empty_path;

        WHEN("A FileValidator is constructed with it")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(bolt::config::FileValidator{empty_path}, std::invalid_argument);
            }
        }
    }
}

SCENARIO("FileValidator accepts a file that satisfies the requested properties")
{
    GIVEN("A validator for an existing regular file")
    {
        const std::filesystem::path file_path =
            std::filesystem::path{BOLT_TEST_DATA_DIRECTORY} / "configuration.toml";

        bolt::config::FileValidator validator{file_path};

        WHEN("It is checked to exist")
        {
            const auto& result = validator.exists();

            THEN("The validator remains usable and preserves the original path")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == file_path);
            }
        }

        WHEN("It is checked to be a regular file")
        {
            const auto& result = validator.is_file();

            THEN("The validator remains usable and preserves the original path")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == file_path);
            }
        }

        WHEN("It is checked to be readable")
        {
            const auto& result = validator.readable();

            THEN("The validator remains usable and preserves the original path")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == file_path);
            }
        }

        WHEN("It is checked to be writable")
        {
            const auto& result = validator.writable();

            THEN("The validator remains usable and preserves the original path")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == file_path);
            }
        }
    }
}

SCENARIO("FileValidator rejects a file that violates the requested properties")
{
    GIVEN("A validator for a non-existent path")
    {
        const std::filesystem::path file_path =
            std::filesystem::path{BOLT_TEST_DATA_DIRECTORY} / "nonexistent.txt";

        bolt::config::FileValidator validator{file_path};

        WHEN("It is checked to exist")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.exists(), std::filesystem::filesystem_error);
            }
        }

        WHEN("It is checked to be a regular file")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.is_file(), std::filesystem::filesystem_error);
            }
        }
    }

    GIVEN("A validator for a path pointing to a directory")
    {
        const std::filesystem::path directory_path{BOLT_TEST_DATA_DIRECTORY};

        bolt::config::FileValidator validator{directory_path};

        WHEN("It is checked to be a regular file")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.is_file(), std::filesystem::filesystem_error);
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("FileValidator rejects a file that violates the requested permissions")
{
    GIVEN("A validator for a file without read permissions")
    {
        const std::filesystem::path file_path =
            std::filesystem::temp_directory_path() / "bolt_config_test_unreadable_file.txt";
        {
            std::ofstream{file_path};
        }
        std::filesystem::permissions(
            file_path, std::filesystem::perms::owner_read, std::filesystem::perm_options::remove
        );
        // NOLINTNEXTLINE(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
        struct Cleanup
        {
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members,misc-non-private-member-variables-in-classes)
            const std::filesystem::path& path;
            ~Cleanup()
            {
                std::filesystem::permissions(
                    path, std::filesystem::perms::owner_all, std::filesystem::perm_options::add
                );
                std::filesystem::remove(path);
            }
        } const cleanup{file_path};

        bolt::config::FileValidator validator{file_path};

        WHEN("It is checked to be readable")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.readable(), std::filesystem::filesystem_error);
            }
        }
    }

    GIVEN("A validator for a file without write permissions")
    {
        const std::filesystem::path file_path =
            std::filesystem::temp_directory_path() / "bolt_config_test_unwritable_file.txt";
        {
            std::ofstream{file_path};
        }
        std::filesystem::permissions(
            file_path, std::filesystem::perms::owner_write, std::filesystem::perm_options::remove
        );

        // NOLINTNEXTLINE(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
        struct Cleanup
        {
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members,misc-non-private-member-variables-in-classes)
            const std::filesystem::path& path;

            ~Cleanup()
            {
                std::filesystem::permissions(
                    path, std::filesystem::perms::owner_all, std::filesystem::perm_options::add
                );
                std::filesystem::remove(path);
            }
        } const cleanup{file_path};

        bolt::config::FileValidator validator{file_path};

        WHEN("It is checked to be writable")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.writable(), std::filesystem::filesystem_error);
            }
        }
    }
}

SCENARIO("DirectoryValidator accepts a valid path on construction")
{
    GIVEN("A non-empty directory path")
    {
        const std::filesystem::path directory_path{BOLT_TEST_DATA_DIRECTORY};

        WHEN("A DirectoryValidator is constructed with it")
        {
            const bolt::config::DirectoryValidator validator{directory_path};

            THEN("The validator stores and returns the path")
            {
                REQUIRE(validator.value() == directory_path);
            }
        }
    }
}

SCENARIO("DirectoryValidator rejects an empty path on construction")
{
    GIVEN("An empty path")
    {
        const std::filesystem::path empty_path;

        WHEN("A DirectoryValidator is constructed with it")
        {
            THEN("An invalid_argument exception is thrown")
            {
                REQUIRE_THROWS_AS(
                    bolt::config::DirectoryValidator{empty_path}, std::invalid_argument
                );
            }
        }
    }
}

SCENARIO("DirectoryValidator accepts a directory that satisfies the requested properties")
{
    GIVEN("A validator for an existing directory")
    {
        const std::filesystem::path directory_path{BOLT_TEST_DATA_DIRECTORY};

        bolt::config::DirectoryValidator validator{directory_path};

        WHEN("It is checked to exist")
        {
            const auto& result = validator.exists();

            THEN("The validator remains usable and preserves the original path")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == directory_path);
            }
        }

        WHEN("It is checked to be a directory")
        {
            const auto& result = validator.is_directory();

            THEN("The validator remains usable and preserves the original path")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == directory_path);
            }
        }

        WHEN("It is checked to be readable")
        {
            const auto& result = validator.readable();

            THEN("The validator remains usable and preserves the original path")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == directory_path);
            }
        }

        WHEN("It is checked to be writable")
        {
            const auto& result = validator.writable();

            THEN("The validator remains usable and preserves the original path")
            {
                REQUIRE(&result == &validator);
                REQUIRE(validator.value() == directory_path);
            }
        }
    }
}

SCENARIO("DirectoryValidator rejects a directory that violates the requested properties")
{
    GIVEN("A validator for a non-existent path")
    {
        const std::filesystem::path directory_path =
            std::filesystem::path{BOLT_TEST_DATA_DIRECTORY} / "nonexistent_dir";

        bolt::config::DirectoryValidator validator{directory_path};

        WHEN("It is checked to exist")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.exists(), std::filesystem::filesystem_error);
            }
        }

        WHEN("It is checked to be a directory")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.is_directory(), std::filesystem::filesystem_error);
            }
        }
    }

    GIVEN("A validator for a path pointing to a regular file")
    {
        const std::filesystem::path file_path =
            std::filesystem::path{BOLT_TEST_DATA_DIRECTORY} / "configuration.toml";

        bolt::config::DirectoryValidator validator{file_path};

        WHEN("It is checked to be a directory")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.is_directory(), std::filesystem::filesystem_error);
            }
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("DirectoryValidator rejects a directory that violates the requested permissions")
{
    GIVEN("A validator for a directory without read permissions")
    {
        const std::filesystem::path directory_path =
            std::filesystem::temp_directory_path() / "bolt_config_test_unreadable_dir";
        std::filesystem::create_directory(directory_path);
        std::filesystem::permissions(
            directory_path, std::filesystem::perms::owner_read,
            std::filesystem::perm_options::remove
        );

        // NOLINTNEXTLINE(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
        struct Cleanup
        {
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members,misc-non-private-member-variables-in-classes)
            const std::filesystem::path& path;

            ~Cleanup()
            {
                std::filesystem::permissions(
                    path, std::filesystem::perms::owner_all, std::filesystem::perm_options::add
                );
                std::filesystem::remove(path);
            }
        } const cleanup{directory_path};

        bolt::config::DirectoryValidator validator{directory_path};

        WHEN("It is checked to be readable")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.readable(), std::filesystem::filesystem_error);
            }
        }
    }

    GIVEN("A validator for a directory without write permissions")
    {
        const std::filesystem::path directory_path =
            std::filesystem::temp_directory_path() / "bolt_config_test_unwritable_dir";
        std::filesystem::create_directory(directory_path);
        std::filesystem::permissions(
            directory_path, std::filesystem::perms::owner_write,
            std::filesystem::perm_options::remove
        );

        // NOLINTNEXTLINE(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
        struct Cleanup
        {
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members,misc-non-private-member-variables-in-classes)
            const std::filesystem::path& path;

            ~Cleanup()
            {
                std::filesystem::permissions(
                    path, std::filesystem::perms::owner_all, std::filesystem::perm_options::add
                );
                std::filesystem::remove(path);
            }
        } const cleanup{directory_path};

        bolt::config::DirectoryValidator validator{directory_path};

        WHEN("It is checked to be writable")
        {
            THEN("A filesystem_error exception is thrown")
            {
                REQUIRE_THROWS_AS(validator.writable(), std::filesystem::filesystem_error);
            }
        }
    }
}
