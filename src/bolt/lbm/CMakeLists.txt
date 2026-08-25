add_library(lbm INTERFACE)

add_library(bolt::lbm ALIAS lbm)

target_include_directories(lbm INTERFACE
    $<BUILD_INTERFACE:${BOLT_INCLUDE_DIRECTORY}/..>
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${BOLT_INSTALL_INCLUDE_DIRECTORY}>
)

target_link_libraries(lbm INTERFACE
    bolt::compile_settings
    bolt::core
)

set_target_properties(lbm PROPERTIES
    OUTPUT_NAME bolt_lbm
)

install(DIRECTORY ${BOLT_INCLUDE_DIRECTORY}/lbm/
    DESTINATION ${BOLT_INSTALL_INCLUDE_DIRECTORY}/lbm
    FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*.tpp"
)

install(TARGETS lbm
    EXPORT bolt-targets
    INCLUDES DESTINATION ${BOLT_INSTALL_INCLUDE_DIRECTORY}
)
