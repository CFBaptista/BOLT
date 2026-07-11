add_executable(apps_test)

target_include_directories(apps_test PRIVATE
    ${CMAKE_SOURCE_DIR}/apps
)

target_compile_features(apps_test PRIVATE cxx_std_23)

target_link_libraries(apps_test PRIVATE
    Catch2::Catch2WithMain
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
)

target_link_options(apps_test PRIVATE
    ${BOLT_LINK_OPTIONS}
)

set_target_properties(apps_test PROPERTIES ${BOLT_COMPILE_PROPERTIES})

catch_discover_tests(apps_test)

target_sources(apps_test PRIVATE
    solver/configuration.cpp
    ${CMAKE_SOURCE_DIR}/apps/solver/configuration.cpp
)
