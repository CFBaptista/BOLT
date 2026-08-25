include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(BOLT_INSTALL_CMAKE_DIRECTORY "${CMAKE_INSTALL_LIBDIR}/cmake/bolt")
set(BOLT_INSTALL_INCLUDE_DIRECTORY ${CMAKE_INSTALL_INCLUDEDIR}/bolt)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/BOLTConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/BOLTConfig.cmake"
    INSTALL_DESTINATION "${BOLT_INSTALL_CMAKE_DIRECTORY}"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/BOLTConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/BOLTConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/BOLTConfigVersion.cmake"
    DESTINATION "${BOLT_INSTALL_CMAKE_DIRECTORY}"
)

install(EXPORT bolt-targets
    FILE BOLTTargets.cmake
    NAMESPACE bolt::
    DESTINATION "${BOLT_INSTALL_CMAKE_DIRECTORY}"
)
