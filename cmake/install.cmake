include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(BOLT_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/BOLT")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/BoltConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/BoltConfig.cmake"
    INSTALL_DESTINATION "${BOLT_INSTALL_CMAKEDIR}"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/BoltConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/BoltConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/BoltConfigVersion.cmake"
    DESTINATION "${BOLT_INSTALL_CMAKEDIR}"
)

install(EXPORT bolt-targets
    FILE BoltTargets.cmake
    NAMESPACE BOLT::
    DESTINATION "${BOLT_INSTALL_CMAKEDIR}"
)
