// Copyright 2026 Stuart Scott
#ifndef ICON_MATERIAL_INCLUDE_PANOMATERIALICON_PROVIDER_H_
#define ICON_MATERIAL_INCLUDE_PANOMATERIALICON_PROVIDER_H_
#include <Pano/icon.h>
#include <SDL3/SDL.h>

class MaterialIconProvider : public Pano::IconProvider {
 public:
  MaterialIconProvider();
  ~MaterialIconProvider() {}

  MaterialIconProvider(const MaterialIconProvider&) = delete;
  MaterialIconProvider& operator=(const MaterialIconProvider&) = delete;
  MaterialIconProvider(MaterialIconProvider&&) = delete;
  MaterialIconProvider& operator=(MaterialIconProvider&&) = delete;

  SDL_Texture* GetIcon(SDL_Renderer* renderer, Pano::Icon icon) override;

 protected:
  SDL_Texture* create_texture(SDL_Renderer* renderer, Pano::Icon icon);
};

MaterialIconProvider* CreateMaterialIconProvider();

#endif  // ICON_MATERIAL_INCLUDE_PANOMATERIALICON_PROVIDER_H_
