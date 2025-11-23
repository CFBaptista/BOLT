# Add inteface library
add_library(lbm INTERFACE)

# Include directories for interface library
target_include_directories(lbm INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Set compile options for interface library
target_compile_options(lbm INTERFACE
    ${COMPILE_FLAGS}
    ${COVERAGE_FLAGS}
)

# Set link options for interface library
target_link_options(lbm INTERFACE
    ${COVERAGE_FLAGS}
)

# Add source files to interface library
target_sources(lbm INTERFACE
    D1Q3.hpp
    D2Q9.hpp
    D3Q27.hpp
    LatticeModelBase.hpp
)
