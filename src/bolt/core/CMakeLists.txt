add_library(core INTERFACE)

target_include_directories(core INTERFACE
    ${BOLT_SOURCE_DIRECTORY}/..
)

target_link_libraries(core INTERFACE
    bolt_compile_settings
)

target_sources(core INTERFACE
    aligned_allocator.hpp
    array.hpp
)
