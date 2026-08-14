include(CTest)
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.1
    SYSTEM
)

FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.6.2
    SYSTEM
)

FetchContent_MakeAvailable(CLI11)

install(
    DIRECTORY "${CLI11_SOURCE_DIR}/include/CLI"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/third_party"
)

set(QUILL_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    quill
    GIT_REPOSITORY https://github.com/odygrd/quill.git
    GIT_TAG v11.1.0
    SYSTEM
)

FetchContent_MakeAvailable(quill)

install(
    DIRECTORY "${quill_SOURCE_DIR}/include/quill"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/third_party"
)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
    SYSTEM
)

FetchContent_MakeAvailable(tomlplusplus)

install(
    DIRECTORY "${tomlplusplus_SOURCE_DIR}/include/toml++"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/third_party"
)
