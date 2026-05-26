add_executable(core_test)

target_link_libraries(core_test PRIVATE
    core
    Catch2::Catch2WithMain
)

target_link_options(core_test PRIVATE
    ${BOLT_LINK_OPTIONS}
)

set_target_properties(core_test PROPERTIES ${BOLT_COMPILE_PROPERTIES})

catch_discover_tests(core_test)

target_sources(core_test PRIVATE
    concepts/LatticeModel.cpp
)
