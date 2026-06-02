add_executable(bolt
    configuration.cpp
    logger.cpp    
    main.cpp
    utilities.cpp
    CommandLineOptions.cpp
)

target_compile_features(bolt PRIVATE cxx_std_23)

target_link_libraries(bolt PRIVATE
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
)
