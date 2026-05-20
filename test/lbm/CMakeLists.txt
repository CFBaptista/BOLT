add_executable(lbm_test)

target_link_libraries(lbm_test PRIVATE
    lbm
    Catch2::Catch2WithMain
)

set_target_properties(lbm_test PROPERTIES ${BOLT_COMPILE_PROPERTIES})

catch_discover_tests(lbm_test)

target_sources(lbm_test PRIVATE
    DistributionField.cpp
    LatticeModel.cpp
)
