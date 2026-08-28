find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/doc/Doxyfile)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doc/doxygen)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    doxygen_add_docs(
        docs
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        CONFIG_FILE ${DOXYGEN_OUT}
        COMMENT "Generating documentation with Doxygen"
    )

    install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT doc
        OPTIONAL
    )
else()
    message(STATUS "Doxygen not found; documentation target will not be available")
endif()
