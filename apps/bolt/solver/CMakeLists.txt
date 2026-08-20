add_executable(bolt)

target_link_libraries(bolt PRIVATE
    bolt::config
    bolt::core
    bolt::lbm
    bolt_compile_settings
)

target_sources(bolt PRIVATE
    configuration.cpp
    LBMSolver.cpp
    main.cpp
)

install(TARGETS bolt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
