execute_process(
    COMMAND "${LLVM_COV_EXECUTABLE}" export
        ${BINARY_ARGS}
        "--instr-profile=${PROFDATA_FILE}"
        "--format=lcov"
        "${SRC_DIR}"
        "${INCLUDE_DIR}"
    OUTPUT_FILE "${LCOV_FILE}"
    COMMAND_ERROR_IS_FATAL ANY
)
