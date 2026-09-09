set(INCLUDE_DIR "../include")

set(LIBRARY_NAME libPanoMaterialIcon)

add_library(${LIBRARY_NAME})

target_sources(${LIBRARY_NAME}
  PRIVATE
    "provider.cpp"

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      "${INCLUDE_DIR}"
    FILES
      "${INCLUDE_DIR}/PanoMaterialIcon/arrow_drop_down.h"
      "${INCLUDE_DIR}/PanoMaterialIcon/check_box_checked.h"
      "${INCLUDE_DIR}/PanoMaterialIcon/check_box_unchecked.h"
      "${INCLUDE_DIR}/PanoMaterialIcon/pano.h"
      "${INCLUDE_DIR}/PanoMaterialIcon/provider.h"
      "${INCLUDE_DIR}/PanoMaterialIcon/radio_button_selected.h"
      "${INCLUDE_DIR}/PanoMaterialIcon/radio_button_unselected.h"
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
  NAMESPACE PanoMaterialIcon::
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

