# Create test executable
add_executable(lbm_test
    D1Q3.cpp
    D2Q9.cpp
    D3Q27.cpp
)

# Link test executable against test framework
target_link_libraries(lbm_test PRIVATE
    Catch2::Catch2WithMain
)

# Set compile flags for test executable
target_compile_options(lbm_test PRIVATE
    ${COMPILE_FLAGS}
    ${COVERAGE_FLAGS}
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

# Set link flags for test executable
target_link_options(lbm_test PRIVATE
    ${COVERAGE_FLAGS}
)

# Discover tests from test executable
catch_discover_tests(lbm_test)
