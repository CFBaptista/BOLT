set(BOLT_CONFIG_HEADERS
    toml_parser.hpp
    validation.hpp
    validation.tpp
    SimulationTime.hpp
    SimulationTime.tpp
)

set(BOLT_CONFIG_SOURCES
    toml_parser.cpp
)

add_library(config STATIC)

add_library(bolt::config ALIAS config)

target_include_directories(config PUBLIC
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(config PUBLIC
    tomlplusplus::tomlplusplus
    bolt_compile_settings
)

target_sources(config PRIVATE
    ${BOLT_CONFIG_SOURCES}
)

set_target_properties(config PROPERTIES
    OUTPUT_NAME bolt_config
)

install(FILES ${BOLT_CONFIG_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/config
)

install(TARGETS config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
