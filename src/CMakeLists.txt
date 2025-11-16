# Copy compile_commands.json from the preset build directory to root build directory
add_custom_target(export_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_BINARY_DIR}/../compile_commands.json"
    COMMENT "Copying compile_commands.json to root build directory"
    VERBATIM
)
