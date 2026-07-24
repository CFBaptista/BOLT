set(BOLT_CONFIGURATION_HEADERS
    configuration_datatypes.hpp
    configuration.hpp
    logger.hpp
    utilities.hpp
    validation.hpp
    validation.tpp
    SimulationTime.hpp
    SimulationTime.tpp
)

set(BOLT_CONFIGURATION_SOURCES
    configuration.cpp
    logger.cpp
    utilities.cpp
)

add_library(configuration STATIC)

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

install(FILES ${BOLT_CONFIGURATION_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/configuration
)

install(TARGETS configuration
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
