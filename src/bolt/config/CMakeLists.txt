add_library(config STATIC)

add_library(bolt::config ALIAS config)

target_include_directories(config PUBLIC
    $<BUILD_INTERFACE:${BOLT_INCLUDE_DIRECTORY}/..>
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${BOLT_INSTALL_INCLUDE_DIRECTORY}>
)

target_link_libraries(config
    PUBLIC
        bolt::compile_settings
    PRIVATE
        CLI11::CLI11
        tomlplusplus::tomlplusplus
)

target_sources(config PRIVATE
    ConfigurationManager.cpp
    configuration_types.cpp
    validation.cpp
)

set_target_properties(config PROPERTIES
    OUTPUT_NAME bolt_config
)

install(DIRECTORY ${BOLT_INCLUDE_DIRECTORY}/config/
    DESTINATION ${BOLT_INSTALL_INCLUDE_DIRECTORY}/config
    FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*.tpp"
)

install(TARGETS config
    EXPORT bolt-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${BOLT_INSTALL_INCLUDE_DIRECTORY}
)
