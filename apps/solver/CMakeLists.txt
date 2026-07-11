add_executable(bolt)

target_include_directories(bolt INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_options(bolt PRIVATE
    -Wno-error=gnu-zero-variadic-macro-arguments
)

target_compile_features(bolt PRIVATE cxx_std_23)

target_link_libraries(bolt PRIVATE
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
    core
    lbm
)

target_sources(bolt PRIVATE
    configuration.cpp
    logger.cpp    
    main.cpp
    utilities.cpp
    LBMSolver.cpp
)
