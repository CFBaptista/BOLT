add_library(core STATIC)

add_library(bolt::core ALIAS core)

target_include_directories(core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${BOLT_INSTALL_INCLUDE_DIRECTORY}>
)

target_link_libraries(core PUBLIC
    quill::quill
    bolt_compile_settings
)

target_sources(core PRIVATE
    logger.cpp
)

set_target_properties(core PROPERTIES
    OUTPUT_NAME bolt_core
)

install(DIRECTORY ${BOLT_INCLUDE_DIRECTORY}/core/
    DESTINATION ${BOLT_INSTALL_INCLUDE_DIRECTORY}/core
    FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*.tpp"
)

install(TARGETS core
    EXPORT bolt-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${BOLT_INSTALL_INCLUDE_DIRECTORY}
)
