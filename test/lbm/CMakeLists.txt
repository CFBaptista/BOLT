add_executable(lbm_test)

target_link_libraries(lbm_test PRIVATE
    lbm
    Catch2::Catch2WithMain
)

target_link_options(lbm_test PRIVATE
    ${BOLT_LINK_OPTIONS}
)

set_target_properties(lbm_test PROPERTIES ${BOLT_COMPILE_PROPERTIES})

catch_discover_tests(lbm_test)

target_sources(lbm_test PRIVATE
    DistributionField.cpp
    LatticeModel.cpp
)
