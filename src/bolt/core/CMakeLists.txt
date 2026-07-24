set(BOLT_CORE_HEADERS
    aligned_allocator.hpp
    array.hpp
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

target_sources(core INTERFACE
    aligned_allocator.hpp
    array.hpp
)

install(FILES ${BOLT_CORE_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
)

install(TARGETS core
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
