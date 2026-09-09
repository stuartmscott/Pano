set(INCLUDE_DIR "include")

set(TARGET_NAME WidgetDemo)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME}
  PRIVATE
    "button.cpp"
    "checkbox.cpp"
    "radio.cpp"
    "ui.cpp"

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      "${INCLUDE_DIR}"
    FILES
      "${INCLUDE_DIR}/PanoWidgetDemo/button.h"
      "${INCLUDE_DIR}/PanoWidgetDemo/checkbox.h"
      "${INCLUDE_DIR}/PanoWidgetDemo/radio.h"
)

target_link_libraries(${TARGET_NAME}
  PRIVATE
    "libPano"
    "libPanoMaterialColor"
    "libPanoMaterialIcon"
    "libPanoNotoSans"
    "SDL3::SDL3"
    "SDL3_image::SDL3_image"
    "SDL3_ttf::SDL3_ttf"
)
