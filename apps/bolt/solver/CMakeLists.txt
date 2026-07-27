add_executable(bolt)

target_include_directories(bolt INTERFACE
    ${BOLT_APPLICATION_DIRECTORY}/..
)

target_link_libraries(bolt PRIVATE
    CLI11::CLI11
    config
    core
    lbm
    bolt_compile_settings
)

target_sources(bolt PRIVATE
    configuration.cpp
    main.cpp
    LBMSolver.cpp
)

install(TARGETS bolt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
