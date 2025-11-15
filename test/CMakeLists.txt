# Check if test framework is installed
find_package(Catch2 3 REQUIRED)

# Create test executable
add_executable(lbm_test)

# Link test executable against test framework
target_link_libraries(lbm_test PRIVATE
    Catch2::Catch2WithMain
)

# Set compile flags for test executable
target_compile_options(lbm_test PRIVATE
    -g
    -O0
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -coverage
)
target_link_options(lbm_test PRIVATE
    -coverage
)

# Discover tests from test executable
include(Catch)
catch_discover_tests(lbm_test)

# Add test directories
add_subdirectory(lbm)
