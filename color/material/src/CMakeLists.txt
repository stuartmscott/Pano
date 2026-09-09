set(INCLUDE_DIR "../include")

set(LIBRARY_NAME libPanoMaterialColor)

add_library(${LIBRARY_NAME})

target_sources(${LIBRARY_NAME}
  PRIVATE
    "dark.cpp"
    "light.cpp"

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      "${INCLUDE_DIR}"
    FILES
      "${INCLUDE_DIR}/PanoMaterialColor/provider.h"
)

target_link_libraries(${LIBRARY_NAME}
  PRIVATE
    "libPano"
    "SDL3::SDL3"
)

install(
  TARGETS ${LIBRARY_NAME}
  EXPORT ${LIBRARY_NAME}Targets
  DESTINATION lib
  FILE_SET HEADERS DESTINATION include
)

install(
  EXPORT ${LIBRARY_NAME}Targets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
  NAMESPACE PanoMaterialColor::
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}"
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}ConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}"
)

