add_executable(core_test)

target_link_libraries(core_test PRIVATE
    Catch2::Catch2WithMain
    bolt::compile_settings
    bolt::core
)

catch_discover_tests(core_test)

target_sources(core_test PRIVATE
    aligned_allocator_test.cpp
    array_test.cpp
    logger_test.cpp
)
