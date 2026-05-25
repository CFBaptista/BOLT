add_library(lbm INTERFACE)

target_include_directories(lbm INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_options(lbm INTERFACE
    ${BOLT_COMPILE_OPTIONS}
)

target_compile_features(lbm INTERFACE
    ${BOLT_COMPILE_FEATURES}
)

target_sources(lbm INTERFACE
    D1Q3.hpp
    D2Q9.hpp
    D3Q27.hpp
    DistributionField.hpp
)
