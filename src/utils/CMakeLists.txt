# Add inteface library
add_library(utils INTERFACE)

# Include directories for interface library
target_include_directories(utils INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Set compile options for interface library
target_compile_options(utils INTERFACE
    ${COMPILE_FLAGS}
    ${COVERAGE_FLAGS}
)

# Set link options for interface library
target_link_options(utils INTERFACE
    ${COVERAGE_FLAGS}
)

# Add source files to interface library
target_sources(utils INTERFACE
    aliases.hpp
)
