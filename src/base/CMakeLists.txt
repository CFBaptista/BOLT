add_library(base INTERFACE)

target_include_directories(base INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_options(base INTERFACE
    ${BOLT_COMPILE_OPTIONS}
)

target_compile_features(base INTERFACE
    ${BOLT_COMPILE_FEATURES}
)

target_sources(base INTERFACE
    AlignedArray.hpp
)
