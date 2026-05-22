find_package(Catch2 3 REQUIRED)
include(Catch)

set(BOLT_COMPILE_PROPERTIES
    CXX_EXTENSIONS OFF
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(BOLT_LINK_OPTIONS
        -fprofile-instr-generate
        -fcoverage-mapping
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(BOLT_LINK_OPTIONS
        --coverage
    )
endif()

add_subdirectory(lbm)
