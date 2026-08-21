add_library(compile_settings INTERFACE)

add_library(bolt::compile_settings ALIAS compile_settings)

set_target_properties(compile_settings PROPERTIES
    CXX_EXTENSIONS OFF
    INTERFACE_CXX_EXTENSIONS OFF
)

target_compile_definitions(compile_settings INTERFACE
    QUILL_COMPILE_ACTIVE_LOG_LEVEL=${QUILL_LOG_LEVEL}
)

target_compile_features(compile_settings INTERFACE
    cxx_std_23
)

target_compile_options(compile_settings INTERFACE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    $<$<CXX_COMPILER_ID:Clang>:-Wno-gnu-zero-variadic-macro-arguments>
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Release>:-O3;-ffast-math;-flto>
    $<$<CONFIG:RelWithDebInfo>:-O2;-g>
    ${BOLT_ARCHITECTURE_FLAGS}
)

if(ENABLE_COVERAGE)
    target_compile_options(compile_settings INTERFACE
        $<$<CXX_COMPILER_ID:Clang>:-fprofile-instr-generate;-fcoverage-mapping>
        $<$<CXX_COMPILER_ID:GNU>:--coverage>
    )

    target_link_options(compile_settings INTERFACE
        $<$<CXX_COMPILER_ID:Clang>:-fprofile-instr-generate;-fcoverage-mapping>
        $<$<CXX_COMPILER_ID:GNU>:--coverage>
    )
endif()

install(TARGETS compile_settings
    EXPORT bolt-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

get_target_property(BOLT_CXX_STANDARD compile_settings CXX_STANDARD)
get_target_property(BOLT_CXX_EXTENSIONS compile_settings CXX_EXTENSIONS)
