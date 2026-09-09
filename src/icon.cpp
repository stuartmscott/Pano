// Copyright 2026 Stuart Scott
#include <Pano/app.h>
#include <Pano/constants.h>
#include <Pano/icon.h>
#include <Pano/log.h>
#include <SDL3_image/SDL_image.h>

namespace Pano {

IconProvider::~IconProvider() {
  for (auto it{icons_.begin()}; it != icons_.end(); ++it) {
    SDL_DestroyTexture(it->second);
  }
  icons_.clear();
}

SDL_Texture* IconProvider::GetIcon(SDL_Renderer* renderer, Icon icon) {
  if (const auto it{icons_.find(icon)}; it != icons_.end()) {
    return it->second;
  }
  return nullptr;
}

SDL_Texture* IconProvider::load_icon(SDL_Renderer* renderer, Icon icon,
                                     const void* data, const size_t size) {
  SDL_IOStream* stream{SDL_IOFromConstMem(data, size)};
  if (stream == nullptr) {
    Error() << "Failed to open stream: " << SDL_GetError() << std::endl;
    return nullptr;
  }
  const auto surface{IMG_LoadSizedSVG_IO(stream, IconSize, IconSize)};
  if (surface == nullptr) {
    Error() << "Failed to create surface: " << SDL_GetError() << std::endl;
    return nullptr;
  }
  const auto texture{SDL_CreateTextureFromSurface(renderer, surface)};
  if (texture == nullptr) {
    Error() << "Failed to create texture: " << SDL_GetError() << std::endl;
  }
  SDL_DestroySurface(surface);
  return texture;
}

void IconView::IconViewArtist::Draw(SDL_Renderer* renderer) {
  View::Artist::Draw(renderer);

  if (texture_ == nullptr) {
    return;
  }

  const auto iv{static_cast<IconView*>(view_)};
  const auto icon{iv->GetIcon()};
  if (icon == Icon::None) {
    return;
  }

  const auto icons{App::current_->GetIconProvider()};
  const auto texture{icons->GetIcon(renderer, icon)};
  if (texture == nullptr) {
    return;
  }

  const auto color{iv->GetColor(Layer::Foreground)};
  const auto halign{iv->GetHorizontalAlignment()};
  const auto valign{iv->GetVerticalAlignment()};
  const auto size{iv->GetSize()};

  Point position;
  switch (halign) {
    case Alignment::Start:
      position.x = 0;
      break;
    case Alignment::Center:
      position.x = (size.width - IconSize) / 2;
      break;
    case Alignment::End:
      position.x = size.width - IconSize;
      break;
  }
  switch (valign) {
    case Alignment::Start:
      position.y = 0;
      break;
    case Alignment::Center:
      position.y = (size.height - IconSize) / 2;
      break;
    case Alignment::End:
      position.y = size.height - IconSize;
      break;
  }

  if (!SDL_SetTextureAlphaMod(texture, color.a)) {
    Error() << "Failed to set alpha modification: " << SDL_GetError()
            << std::endl;
  }
  if (!SDL_SetTextureColorMod(texture, color.r, color.g, color.b)) {
    Error() << "Failed to set color modification: " << SDL_GetError()
            << std::endl;
  }
  if (!SDL_SetRenderTarget(renderer, texture_)) {
    Error() << "Failed to set render target: " << SDL_GetError() << std::endl;
  }
  if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
    Error() << "Failed to set blend mode: " << SDL_GetError() << std::endl;
  }
  if (!SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND)) {
    Error() << "Failed to set blend mode: " << SDL_GetError() << std::endl;
  }
  SDL_FRect src{0, 0, IconSize, IconSize};
  SDL_FRect dest{position.x, position.y, IconSize, IconSize};
  if (!SDL_RenderTexture(renderer, texture, &src, &dest)) {
    Error() << "Failed to render texture: " << SDL_GetError() << std::endl;
  }
}
};  // namespace Pano
