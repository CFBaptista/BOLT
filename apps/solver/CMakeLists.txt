add_executable(bolt
    configuration.cpp
    logger.cpp    
    main.cpp
    utilities.cpp
    CommandLineOptions.cpp
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

target_include_directories(bolt SYSTEM PRIVATE
    ${CLI11_INCLUDE_DIRS}
    ${QUILL_INCLUDE_DIRS}
    ${TOMLPLUSPLUS_INCLUDE_DIRS}
)
