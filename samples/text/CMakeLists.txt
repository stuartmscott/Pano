set(TARGET_NAME TextDemo)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME}
  PRIVATE
    "ui.cpp"
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
