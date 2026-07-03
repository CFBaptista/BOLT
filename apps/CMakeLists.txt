include(FetchContent)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.6.2
    SYSTEM
)

FetchContent_MakeAvailable(CLI11)
get_target_property(CLI11_INCLUDE_DIRS CLI11::CLI11 INTERFACE_INCLUDE_DIRECTORIES)

FetchContent_Declare(
    quill
    GIT_REPOSITORY https://github.com/odygrd/quill.git
    GIT_TAG v11.1.0
    SYSTEM
)

FetchContent_MakeAvailable(quill)
get_target_property(QUILL_INCLUDE_DIRS quill::quill INTERFACE_INCLUDE_DIRECTORIES)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
    SYSTEM
)

FetchContent_MakeAvailable(tomlplusplus)
get_target_property(TOMLPLUSPLUS_INCLUDE_DIRS tomlplusplus::tomlplusplus INTERFACE_INCLUDE_DIRECTORIES)

add_subdirectory(solver)
