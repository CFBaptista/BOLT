set(BOLT_CONFIG_HEADERS
    toml_parser.hpp
    toml_parser.tpp
    validation.hpp
    validation.tpp
    SimulationTime.hpp
    SimulationTime.tpp
)

set(BOLT_CONFIG_SOURCES
)

add_library(config INTERFACE)

add_library(bolt::config ALIAS config)

target_include_directories(config INTERFACE
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(config INTERFACE
    tomlplusplus::tomlplusplus
    bolt_compile_settings
)

set_target_properties(config PROPERTIES
    OUTPUT_NAME bolt_config
)

install(FILES ${BOLT_CONFIG_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/config
)

install(TARGETS config tomlplusplus_tomlplusplus
    EXPORT bolt-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
