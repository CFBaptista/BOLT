add_executable(config_test)

target_link_libraries(config_test PRIVATE    
    Catch2::Catch2WithMain
    tomlplusplus::tomlplusplus
    bolt::compile_settings
    bolt::config
)

catch_discover_tests(config_test)

target_sources(config_test PRIVATE
    toml_parser_test.cpp
    validation_test.cpp
    SimulationTime_test.cpp
)
