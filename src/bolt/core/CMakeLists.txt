set(BOLT_CORE_HEADERS
    aligned_allocator.hpp
    aligned_allocator.tpp
    array.hpp
    array.tpp
    logger.hpp
    timestamp.hpp
)

set(BOLT_CORE_SOURCES
    logger.cpp
    timestamp.cpp
)

add_library(core STATIC)

add_library(bolt::core ALIAS core)

target_include_directories(core PUBLIC
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(core PUBLIC
    quill::quill
    bolt_compile_settings
)

target_sources(core PRIVATE
    ${BOLT_CORE_SOURCES}
)

set_target_properties(core PROPERTIES
    OUTPUT_NAME bolt_core
)

install(FILES ${BOLT_CORE_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
)

install(TARGETS core
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
