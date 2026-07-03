add_executable(bolt
    configuration.cpp
    logger.cpp    
    main.cpp
    utilities.cpp
    LBMSolver.cpp
)

target_compile_features(bolt PRIVATE cxx_std_23)

target_compile_options(bolt PRIVATE
    -Wno-error=gnu-zero-variadic-macro-arguments
)

target_link_libraries(bolt PRIVATE
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
    core
)
