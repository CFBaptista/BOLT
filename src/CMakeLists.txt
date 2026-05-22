# Define compile flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BOLT_COMPILE_FLAGS
        -O0
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BOLT_COMPILE_FLAGS
        -O3
        -ffast-math
        -march=native
        -mtune=native
        -flto
    )
endif()

# Define coverage flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(BOLT_COVERAGE_FLAGS
        -fprofile-instr-generate
        -fcoverage-mapping
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(BOLT_COVERAGE_FLAGS
        --coverage
    )
endif()

set(BOLT_WARNING_FLAGS
  -Wall
  -Wextra
  -Werror
  -Wpedantic
)

# Merge flags into compile options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BOLT_COMPILE_OPTIONS
        ${BOLT_COMPILE_FLAGS}
        ${BOLT_COVERAGE_FLAGS}
        ${BOLT_WARNING_FLAGS}
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BOLT_COMPILE_OPTIONS
        ${BOLT_COMPILE_FLAGS}
        ${BOLT_WARNING_FLAGS}
    )
endif()

set(BOLT_COMPILE_FEATURES
    cxx_std_23
)

add_subdirectory(base)
add_subdirectory(lbm)
