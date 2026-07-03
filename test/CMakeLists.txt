include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.1
    SYSTEM
)

FetchContent_MakeAvailable(Catch2)
include(Catch)
get_target_property(CATCH2_INCLUDE_DIRECTORIES Catch2 INTERFACE_INCLUDE_DIRECTORIES)

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

add_subdirectory(core)
add_subdirectory(lbm)
