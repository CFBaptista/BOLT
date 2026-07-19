add_executable(solver_test)

target_link_libraries(solver_test PRIVATE    
    Catch2::Catch2WithMain
    configuration
    bolt_compile_settings
)

catch_discover_tests(solver_test)

target_sources(solver_test PRIVATE
    SimulationTime.cpp    
    configuration.cpp
)
