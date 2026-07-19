include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.1
    SYSTEM
)

FetchContent_MakeAvailable(Catch2)

get_target_property(
    CATCH2_INCLUDE_DIRECTORIES
    Catch2
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    Catch2 
    PROPERTIES
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${CATCH2_INCLUDE_DIRECTORIES}"
)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.6.2
    SYSTEM
)

FetchContent_MakeAvailable(CLI11)

get_target_property(
    CLI11_INCLUDE_DIRS 
    CLI11
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    CLI11
    PROPERTIES
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${CLI11_INCLUDE_DIRS}"
)

FetchContent_Declare(
    quill
    GIT_REPOSITORY https://github.com/odygrd/quill.git
    GIT_TAG v11.1.0
    SYSTEM
)

FetchContent_MakeAvailable(quill)

get_target_property(
    QUILL_INCLUDE_DIRS 
    quill
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    quill
    PROPERTIES
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${QUILL_INCLUDE_DIRS}"
)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
    SYSTEM
)

FetchContent_MakeAvailable(tomlplusplus)

get_target_property(
    TOMLPLUSPLUS_INCLUDE_DIRS
    tomlplusplus_tomlplusplus
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    tomlplusplus_tomlplusplus
    PROPERTIES
        INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${TOMLPLUSPLUS_INCLUDE_DIRS}"
)
