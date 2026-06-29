include(FetchContent)

FetchContent_Declare(
    CLI11
    SYSTEM
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.6.2
)

FetchContent_MakeAvailable(CLI11)

FetchContent_Declare(
    quill
    SYSTEM
    GIT_REPOSITORY https://github.com/odygrd/quill.git
    GIT_TAG v11.1.0
)

FetchContent_MakeAvailable(quill)

FetchContent_Declare(
    tomlplusplus
    SYSTEM
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(tomlplusplus)

add_subdirectory(solver)
