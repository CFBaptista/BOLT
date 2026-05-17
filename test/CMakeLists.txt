find_package(Catch2 3 REQUIRED)
include(Catch)

set(BOLT_COMPILE_PROPERTIES
    CXX_EXTENSIONS OFF
)

add_subdirectory(lbm)
