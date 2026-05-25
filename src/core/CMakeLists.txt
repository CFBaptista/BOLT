add_library(core INTERFACE)

target_include_directories(core INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_options(core INTERFACE
    ${BOLT_COMPILE_OPTIONS}
)

target_compile_features(core INTERFACE
    ${BOLT_COMPILE_FEATURES}
)

target_sources(core INTERFACE
    containers/AlignedArray.hpp
)
