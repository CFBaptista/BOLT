if(ENABLE_DOCUMENTATION)
    find_package(Doxygen REQUIRED)
    set(ALWAYS_BUILD_DOCUMENTATION "ALL")
else()
    find_package(Doxygen)
    set(ALWAYS_BUILD_DOCUMENTATION "")
endif()

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/doc/doxygen/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(
        Doxygen ${ALWAYS_BUILD_DOCUMENTATION}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
