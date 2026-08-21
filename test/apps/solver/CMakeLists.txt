add_executable(solver_test)

target_include_directories(solver_test PRIVATE
    ${BOLT_APPLICATION_DIRECTORY}/..
)

target_link_libraries(solver_test PRIVATE    
    Catch2::Catch2WithMain
    CLI11::CLI11
    config
    bolt::compile_settings
)

catch_discover_tests(solver_test)

target_sources(solver_test PRIVATE
    configuration_test.cpp    
    ${BOLT_APPLICATION_DIRECTORY}/solver/configuration.cpp
)
