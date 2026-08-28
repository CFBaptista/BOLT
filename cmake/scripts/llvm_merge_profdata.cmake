file(GLOB profraw_files LIST_DIRECTORIES false "${PROFRAW_DIR}/*.profraw")

if(NOT profraw_files)
    message(FATAL_ERROR "No .profraw files found in '${PROFRAW_DIR}'. "
        "Ensure tests ran with -fprofile-instr-generate and -fcoverage-mapping flags.")
endif()

execute_process(
    COMMAND "${LLVM_PROFDATA_EXECUTABLE}" merge -sparse ${profraw_files} -o "${PROFDATA_FILE}"
    COMMAND_ERROR_IS_FATAL ANY
)
