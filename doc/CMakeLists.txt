find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/doc/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    doxygen_add_docs(
        documentation
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        CONFIG_FILE ${DOXYGEN_OUT}
        COMMENT "Generating documentation with Doxygen"
    )
else()
    message(STATUS "Doxygen not found; documentation target will not be available")
endif()
