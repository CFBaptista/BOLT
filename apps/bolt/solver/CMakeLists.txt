set(BOLT_APP_HEADERS
    configuration.hpp
    LBMSolver.hpp
)

set(BOLT_APP_SOURCES
    configuration.cpp
    LBMSolver.cpp
    main.cpp
)

add_executable(bolt)

target_include_directories(bolt INTERFACE
    ${BOLT_APPLICATION_DIRECTORY}/..
)

target_link_libraries(bolt PRIVATE
    config
    core
    lbm
    bolt_compile_settings
)

target_sources(bolt PRIVATE
    ${BOLT_APP_SOURCES}
)

install(TARGETS bolt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
