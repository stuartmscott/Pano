################################################################
# Tests

set(TARGET_NAME PanoTests)

set(INCLUDE_DIR "../include")

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME}
  PRIVATE
    "constants.cpp"
    "golden.cpp"
    "typesetting.cpp"
    "utf.cpp"

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      "${INCLUDE_DIR}"
    FILES
      "${INCLUDE_DIR}/PanoTest/app.h"
      "${INCLUDE_DIR}/PanoTest/constants.h"
      "${INCLUDE_DIR}/PanoTest/golden.h"
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
    "gtest_main"
)

# Fetch GoogleTest Library
include(FetchContent)
FetchContent_Declare(
  GoogleTest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        063de7e9578f82b369302001269680b4b1553359 # release-1.18.0
)
set(INSTALL_GTEST OFF CACHE BOOL "Enable installation of googletest." FORCE)
FetchContent_MakeAvailable(GoogleTest)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
