add_executable(lbm_test)

target_link_libraries(lbm_test PRIVATE    
    Catch2::Catch2WithMain
    bolt::lbm
    bolt_compile_settings
)

catch_discover_tests(lbm_test)

target_sources(lbm_test PRIVATE
    D1Q3_test.cpp
    D2Q9_test.cpp
    D3Q27_test.cpp
    DistributionField_test.cpp
    LatticeModel_test.cpp
)
