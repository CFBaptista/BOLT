set(BOLT_CONFIG_HEADERS
    configuration_types.hpp
    toml_parser.hpp
    toml_parser.tpp
    validation.hpp
    validation.tpp
    SimulationTime.hpp
    SimulationTime.tpp
)

set(BOLT_CONFIG_SOURCES
    configuration_types.cpp
    validation.cpp
)

add_library(config STATIC)

add_library(bolt::config ALIAS config)

target_include_directories(config PUBLIC
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(config PUBLIC
    CLI11::CLI11
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

install(TARGETS config CLI11 tomlplusplus_tomlplusplus
    EXPORT bolt-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
