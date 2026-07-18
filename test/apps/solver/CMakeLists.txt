add_executable(solver_test)

target_link_libraries(solver_test PRIVATE
    configuration
    Catch2::Catch2WithMain
)

target_link_options(solver_test PRIVATE
    ${BOLT_LINK_OPTIONS}
)

set_target_properties(solver_test PROPERTIES ${BOLT_COMPILE_PROPERTIES})

catch_discover_tests(solver_test)

target_sources(solver_test PRIVATE
    configuration.cpp
)
