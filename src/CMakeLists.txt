if(CMAKE_EXPORT_COMPILE_COMMANDS)
    add_custom_target(copy_compile_commands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/build/compile_commands.json
        BYPRODUCTS ${CMAKE_SOURCE_DIR}/build/compile_commands.json
        COMMENT "Copying compile_commands.json from preset build directory to root build directory"
        VERBATIM
    )
endif()

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

add_subdirectory(core)
add_subdirectory(lbm)
