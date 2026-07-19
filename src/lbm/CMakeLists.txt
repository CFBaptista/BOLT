add_library(lbm INTERFACE)

target_include_directories(lbm INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(lbm INTERFACE
    bolt_compile_settings
)

target_sources(lbm INTERFACE
    D1Q3.hpp
    D2Q9.hpp
    D3Q27.hpp
    DistributionField.hpp
)
