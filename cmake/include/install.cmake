include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install_external_project(Catch2)
install_external_project(CLI11)
install_external_project(quill)
install_external_project(tomlplusplus)

set(BOLT_INSTALL_CMAKE_DIRECTORY "${CMAKE_INSTALL_LIBDIR}/cmake/BOLT")
set(BOLT_INSTALL_INCLUDE_DIRECTORY ${CMAKE_INSTALL_INCLUDEDIR}/bolt)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/BoltConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/BoltConfig.cmake"
    INSTALL_DESTINATION "${BOLT_INSTALL_CMAKE_DIRECTORY}"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/BoltConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/BoltConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/BoltConfigVersion.cmake"
    DESTINATION "${BOLT_INSTALL_CMAKE_DIRECTORY}"
)

install(EXPORT bolt-targets
    FILE BoltTargets.cmake
    NAMESPACE bolt::
    DESTINATION "${BOLT_INSTALL_CMAKE_DIRECTORY}"
)
