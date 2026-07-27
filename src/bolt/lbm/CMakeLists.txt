set(BOLT_LBM_HEADERS
    D1Q3.hpp
    D2Q9.hpp
    D3Q27.hpp
    DistributionField.hpp
    DistributionField.tpp
    LatticeModel.hpp
)

set(BOLT_LBM_SOURCES
)

add_library(lbm INTERFACE)

add_library(bolt::lbm ALIAS lbm)

target_include_directories(lbm INTERFACE
    $<BUILD_INTERFACE:${BOLT_SOURCE_DIRECTORY}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(lbm INTERFACE
    bolt_compile_settings
)

set_target_properties(lbm PROPERTIES
    OUTPUT_NAME bolt_lbm
)

install(FILES ${BOLT_LBM_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lbm
)

install(TARGETS lbm
    EXPORT bolt-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
