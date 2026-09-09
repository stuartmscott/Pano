set(INCLUDE_DIR "include")

set(TARGET_NAME LayoutDemo)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME}
  PRIVATE
    "edge.cpp"
    "grid.cpp"
    "stack.cpp"
    "tab.cpp"
    "ui.cpp"

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      "${INCLUDE_DIR}"
    FILES
      "${INCLUDE_DIR}/PanoLayoutDemo/edge.h"
      "${INCLUDE_DIR}/PanoLayoutDemo/grid.h"
      "${INCLUDE_DIR}/PanoLayoutDemo/palette.h"
      "${INCLUDE_DIR}/PanoLayoutDemo/stack.h"
      "${INCLUDE_DIR}/PanoLayoutDemo/tab.h"
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
