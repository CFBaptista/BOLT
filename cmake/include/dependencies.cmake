if(BUILD_TESTING)
    include(CTest)

    provide_dependency(
        "Catch2"
        "https://github.com/catchorg/Catch2.git"
        "v3.15.1"
        "-DBUILD_SHARED_LIBS=OFF;-DCATCH_DEVELOPMENT_BUILD=OFF"
        ${USE_SYSTEM_CATCH2}
    )
endif()

provide_dependency(
    "CLI11"
    "https://github.com/CLIUtils/CLI11.git"
    "v2.6.2"
    "-DCLI11_BUILD_TESTS=OFF;-DCLI11_BUILD_EXAMPLES=OFF;-DCLI11_BUILD_DOCS=OFF"
    ${USE_SYSTEM_CLI11}
)

provide_dependency(
    "quill"
    "https://github.com/odygrd/quill.git"
    "v11.1.0"
    "-DBUILD_SHARED_LIBS=OFF"
    ${USE_SYSTEM_QUILL}
)

provide_dependency(
    "tomlplusplus"
    "https://github.com/marzer/tomlplusplus.git"
    "v3.4.0"
    "-DBUILD_SHARED_LIBS=OFF"
    ${USE_SYSTEM_TOMLPLUSPLUS}
)
