# Check if test framework is installed
find_package(Catch2 3 REQUIRED)
include(Catch)

# Add test directories
add_subdirectory(lbm)
