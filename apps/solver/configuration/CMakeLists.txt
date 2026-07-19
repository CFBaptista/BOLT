add_library(configuration STATIC)

target_include_directories(configuration PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(configuration PUBLIC
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
    core
    lbm
    bolt_compile_settings
)

target_sources(configuration
    PUBLIC
        utilities.hpp
        validation.hpp
    PRIVATE
        configuration.cpp
        logger.cpp
        utilities.cpp
)
