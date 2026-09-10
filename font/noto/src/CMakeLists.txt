set(INCLUDE_DIR "../include")

set(LIBRARY_NAME libPanoNotoSans)

add_library(${LIBRARY_NAME})

target_sources(${LIBRARY_NAME}
  PRIVATE
    "provider.cpp"

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      "${INCLUDE_DIR}"
    FILES
      "${INCLUDE_DIR}/PanoNotoSans/notosans_bold.h"
      "${INCLUDE_DIR}/PanoNotoSans/notosans_bolditalic.h"
      "${INCLUDE_DIR}/PanoNotoSans/notosans_italic.h"
      "${INCLUDE_DIR}/PanoNotoSans/notosans_regular.h"
      "${INCLUDE_DIR}/PanoNotoSans/notosansmath_regular.h"
      "${INCLUDE_DIR}/PanoNotoSans/provider.h"
)

target_link_libraries(${LIBRARY_NAME}
  PUBLIC
    "libPano"
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
  NAMESPACE PanoNotoSans::
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

