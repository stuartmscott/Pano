set(INCLUDE_DIR "../include")

set(LIBRARY_NAME libPano)

add_library(${LIBRARY_NAME})

target_sources(${LIBRARY_NAME}
  PRIVATE
    "app.cpp"
    "button.cpp"
    "checkbox.cpp"
    "color.cpp"
    "edge.cpp"
    "font.cpp"
    "frame.cpp"
    "grid.cpp"
    "group.cpp"
    "icon.cpp"
    "log.cpp"
    "radio.cpp"
    "stack.cpp"
    "tab.cpp"
    "text.cpp"
    "typesetting.cpp"
    "utf.cpp"
    "view.cpp"
    "window.cpp"

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      "${INCLUDE_DIR}"
    FILES
      "${INCLUDE_DIR}/Pano/animation.h"
      "${INCLUDE_DIR}/Pano/app.h"
      "${INCLUDE_DIR}/Pano/button.h"
      "${INCLUDE_DIR}/Pano/checkbox.h"
      "${INCLUDE_DIR}/Pano/color.h"
      "${INCLUDE_DIR}/Pano/constants.h"
      "${INCLUDE_DIR}/Pano/edge.h"
      "${INCLUDE_DIR}/Pano/icon.h"
      "${INCLUDE_DIR}/Pano/font.h"
      "${INCLUDE_DIR}/Pano/frame.h"
      "${INCLUDE_DIR}/Pano/geometry.h"
      "${INCLUDE_DIR}/Pano/grid.h"
      "${INCLUDE_DIR}/Pano/group.h"
      "${INCLUDE_DIR}/Pano/log.h"
      "${INCLUDE_DIR}/Pano/radio.h"
      "${INCLUDE_DIR}/Pano/stack.h"
      "${INCLUDE_DIR}/Pano/tab.h"
      "${INCLUDE_DIR}/Pano/text.h"
      "${INCLUDE_DIR}/Pano/typesetting.h"
      "${INCLUDE_DIR}/Pano/view.h"
      "${INCLUDE_DIR}/Pano/utf.h"
      "${INCLUDE_DIR}/Pano/window.h"
)

target_link_libraries(${LIBRARY_NAME}
  PRIVATE
    "SDL3::SDL3"
    "SDL3_image::SDL3_image"
    "SDL3_ttf::SDL3_ttf"
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
  NAMESPACE Pano::
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

