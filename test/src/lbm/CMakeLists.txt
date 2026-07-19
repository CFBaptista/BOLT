add_executable(lbm_test)

target_link_libraries(lbm_test PRIVATE    
    Catch2::Catch2WithMain
    lbm
    bolt_compile_settings
)

catch_discover_tests(lbm_test)

target_sources(lbm_test PRIVATE
    D1Q3.cpp
    D2Q9.cpp
    D3Q27.cpp
    DistributionField.cpp
)
