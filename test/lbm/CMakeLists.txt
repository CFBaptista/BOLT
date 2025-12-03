# Create test executable
add_executable(lbm_test)

# Link test executable against test framework
target_link_libraries(lbm_test PRIVATE
    lbm
    Catch2::Catch2WithMain
)

# Set compile flags for test executable
target_compile_options(lbm_test PRIVATE
    ${COMPILE_FLAGS}
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

# Discover tests from test executable
catch_discover_tests(lbm_test)

# Add source files to test executable
target_sources(lbm_test PRIVATE
    D1Q3.cpp
    D2Q9.cpp
    D3Q27.cpp
    VelocitySetBase.cpp
)
