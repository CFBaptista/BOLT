set(BOLT_CORE_HEADERS
    aligned_allocator.hpp
    aligned_allocator.tpp
    array.hpp
    array.tpp
)

set(BOLT_CORE_SOURCES
)

add_library(core INTERFACE)

target_include_directories(core INTERFACE
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(core INTERFACE
    bolt_compile_settings
)

install(FILES ${BOLT_CORE_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
)

install(TARGETS core
    EXPORT bolt-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
