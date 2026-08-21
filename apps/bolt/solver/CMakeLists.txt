add_executable(bolt)

target_link_libraries(bolt PRIVATE
    bolt::compile_settings
    bolt::config
    bolt::core
    bolt::lbm
)

target_sources(bolt PRIVATE
    configuration.cpp
    LBMSolver.cpp
    main.cpp
)

install(TARGETS bolt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
