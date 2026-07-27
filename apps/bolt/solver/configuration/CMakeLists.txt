set(BOLT_CONFIGURATION_HEADERS
    logger.hpp
    utilities.hpp
    validation.hpp
    validation.tpp
    SimulationTime.hpp
    SimulationTime.tpp
)

set(BOLT_CONFIGURATION_SOURCES
    logger.cpp
    utilities.cpp
)

add_library(configuration STATIC)

add_library(bolt::configuration ALIAS configuration)

target_include_directories(configuration PUBLIC
    $<BUILD_INTERFACE:${BOLT_APPLICATION_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(configuration PUBLIC
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
    core
    lbm
    bolt_compile_settings
)

target_sources(configuration PRIVATE
    ${BOLT_CONFIGURATION_SOURCES}
)

set_target_properties(configuration PROPERTIES
    OUTPUT_NAME bolt_configuration
)

install(FILES ${BOLT_CONFIGURATION_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/configuration
)

install(TARGETS configuration
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
