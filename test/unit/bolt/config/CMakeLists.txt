add_executable(config_test)

target_link_libraries(config_test PRIVATE    
    Catch2::Catch2WithMain
    tomlplusplus::tomlplusplus
    bolt::compile_settings
    bolt::config
)

target_compile_definitions(config_test PRIVATE
    BOLT_TEST_DATA_DIRECTORY="${CMAKE_SOURCE_DIR}/test/data"
)

catch_discover_tests(config_test)

target_sources(config_test PRIVATE
    ConfigurationManager_test.cpp
    configuration_types_test.cpp
    toml_parser_test.cpp
    validation_test.cpp
    SimulationTime_test.cpp
)
