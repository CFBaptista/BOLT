add_executable(bolt)

target_include_directories(bolt INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_options(bolt PRIVATE
    ${BOLT_COMPILE_OPTIONS}
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(bolt PRIVATE --coverage)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_options(bolt PRIVATE -fprofile-instr-generate -fcoverage-mapping)
endif()

target_link_options(bolt PRIVATE
    ${BOLT_LINK_OPTIONS}
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
