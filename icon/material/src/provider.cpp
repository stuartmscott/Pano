// Copyright 2026 Stuart Scott
#include <Pano/icon.h>
#include <PanoMaterialIcon/arrow_drop_down.h>
#include <PanoMaterialIcon/check_box_checked.h>
#include <PanoMaterialIcon/check_box_unchecked.h>
#include <PanoMaterialIcon/pano.h>
#include <PanoMaterialIcon/provider.h>
#include <PanoMaterialIcon/radio_button_selected.h>
#include <PanoMaterialIcon/radio_button_unselected.h>
#include <SDL3/SDL.h>

using namespace Pano;

MaterialIconProvider::MaterialIconProvider() : IconProvider() {}

SDL_Texture* MaterialIconProvider::GetIcon(SDL_Renderer* renderer, Icon icon) {
  SDL_Texture* texture{IconProvider::GetIcon(renderer, icon)};
  if (texture != nullptr) {
    return texture;
  }
  texture = create_texture(renderer, icon);
  if (texture != nullptr) {
    SetIcon(icon, texture);
  }
  return texture;
}

SDL_Texture* MaterialIconProvider::create_texture(SDL_Renderer* renderer,
                                                  Icon icon) {
  switch (icon) {
    case Icon::None:
      return nullptr;
    case Icon::ArrowDropDown:
      return load_icon(renderer, icon, arrow_drop_down, arrow_drop_down_len);
    case Icon::CheckBoxChecked:
      return load_icon(renderer, icon, check_box_checked,
                       check_box_checked_len);
    case Icon::CheckBoxUnchecked:
      return load_icon(renderer, icon, check_box_unchecked,
                       check_box_unchecked_len);
    case Icon::Pano:
      return load_icon(renderer, icon, pano, pano_len);
    case Icon::RadioButtonSelected:
      return load_icon(renderer, icon, radio_button_selected,
                       radio_button_selected_len);
    case Icon::RadioButtonUnselected:
      return load_icon(renderer, icon, radio_button_unselected,
                       radio_button_unselected_len);
  }
}

MaterialIconProvider* CreateMaterialIconProvider() {
  return new MaterialIconProvider();
}
