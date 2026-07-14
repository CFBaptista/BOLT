add_executable(bolt)

target_include_directories(bolt INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_options(bolt PRIVATE
    -Wno-error=gnu-zero-variadic-macro-arguments
)

target_compile_features(bolt PRIVATE cxx_std_23)

add_subdirectory(configuration)

target_link_libraries(bolt PRIVATE
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
    core
    lbm
    configuration
)

target_sources(bolt PRIVATE
    main.cpp
    LBMSolver.cpp
)
