set(BOLT_CORE_HEADERS
    aligned_allocator.hpp
    aligned_allocator.tpp
    array.hpp
    array.tpp
)

set(BOLT_CORE_SOURCES
)

add_library(core INTERFACE)

add_library(bolt::core ALIAS core)

target_include_directories(core INTERFACE
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(core INTERFACE
    bolt_compile_settings
)

set_target_properties(core PROPERTIES
    OUTPUT_NAME bolt_core
)

install(FILES ${BOLT_CORE_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
)

install(TARGETS core
    EXPORT bolt-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
