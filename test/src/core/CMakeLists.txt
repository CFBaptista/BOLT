add_executable(core_test)

target_link_libraries(core_test PRIVATE
    Catch2::Catch2WithMain
    core
    bolt_compile_settings
)

catch_discover_tests(core_test)

target_sources(core_test PRIVATE
    concepts/LatticeModel.cpp
    time/SimulationTime.cpp
)
