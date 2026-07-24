add_executable(bolt)

target_include_directories(bolt INTERFACE
    ${BOLT_APPLICATION_DIRECTORY}/..
)

add_subdirectory(configuration)

target_link_libraries(bolt PRIVATE
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
    core
    lbm
    configuration
    bolt_compile_settings
)

target_sources(bolt PRIVATE
    main.cpp
    LBMSolver.cpp
)

install(TARGETS bolt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
