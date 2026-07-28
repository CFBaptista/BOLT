add_executable(config_test)

target_link_libraries(config_test PRIVATE    
    Catch2::Catch2WithMain
    config
    bolt_compile_settings
)

catch_discover_tests(config_test)

target_sources(config_test PRIVATE
    toml_parser.cpp
    validation.cpp
    SimulationTime.cpp
)
