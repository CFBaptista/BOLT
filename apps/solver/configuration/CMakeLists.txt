add_library(configuration STATIC)

target_include_directories(configuration PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# target_compile_options(configuration PUBLIC
#
# )

target_compile_features(configuration PRIVATE cxx_std_23)

target_link_libraries(configuration PUBLIC
    CLI11::CLI11
    quill::quill
    tomlplusplus::tomlplusplus
    core
    lbm
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
