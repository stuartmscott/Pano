// Copyright 2026 Stuart Scott
#include <Pano/font.h>
#include <Pano/log.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <sstream>
#include <string>
#include <utility>

namespace Pano {

int Font::GetAdvance(char32_t c) {
  int min_x;
  int max_x;
  int min_y;
  int max_y;
  int advance;
  GetMetrics(c, &min_x, &max_x, &min_y, &max_y, &advance);
  return advance;
}

void Font::GetMetrics(char32_t c, int* min_x, int* max_x, int* min_y,
                      int* max_y, int* advance) {
  if (!TTF_GetGlyphMetrics(font_, c, min_x, max_x, min_y, max_y, advance)) {
    Error() << "Failed to get glyph metrics: " << SDL_GetError() << std::endl;
  }
}

int Font::GetKerning(char32_t a, char32_t b) {
  int kerning{0};
  if (!TTF_GetGlyphKerning(font_, a, b, &kerning)) {
    Error() << "Failed to get glyph kerning: " << SDL_GetError() << std::endl;
  }
  return kerning;
}

void Font::Draw(SDL_Renderer* renderer, std::string string, Point position,
                SDL_Color color) {
  const auto texture{get_texture(renderer, string, color)};
  if (texture.first == nullptr) {
    return;
  }
  if (!SDL_SetTextureBlendMode(texture.first, SDL_BLENDMODE_BLEND)) {
    Error() << "Failed to set blend mode: " << SDL_GetError() << std::endl;
  }
  SDL_FRect src{0, 0, texture.second.width, texture.second.height};
  SDL_FRect dest{position.x, position.y, texture.second.width,
                 texture.second.height};
  Debug() << "Draw: " << string << '@' << dest.x << ',' << dest.y << ' '
          << dest.w << 'x' << dest.h << std::endl;
  if (!SDL_RenderTexture(renderer, texture.first, &src, &dest)) {
    Error() << "Failed to render texture: " << SDL_GetError() << std::endl;
  }
}

std::pair<SDL_Texture*, Size> Font::get_texture(SDL_Renderer* renderer,
                                                std::string string,
                                                SDL_Color color) {
  const auto id = std::make_tuple(string, color.r, color.g, color.b, color.a);
  if (const auto it{textures_.find(id)}; it != textures_.end()) {
    return it->second;
  }

  const auto surface{TTF_RenderText_Blended(font_, string.c_str(), 0, color)};
  // const auto surface{TTF_RenderText_Solid(font_, string.c_str(), 0, color)};
  if (surface == nullptr) {
    Error() << "Failed to render text: " << SDL_GetError() << std::endl;
  } else {
    Size size{static_cast<float>(surface->w), static_cast<float>(surface->h)};
    const auto texture{SDL_CreateTextureFromSurface(renderer, surface)};
    if (texture == nullptr) {
      Error() << "Failed to create texture: " << SDL_GetError() << std::endl;
    } else {
      return textures_[id] = std::make_pair(texture, size);
    }
    SDL_DestroySurface(surface);
  }
  return std::make_pair(nullptr, Size{});
}

FontProvider::~FontProvider() {
  for (auto it{fonts_.begin()}; it != fonts_.end(); ++it) {
    delete it->second;
  }
  fonts_.clear();
}

Font* FontProvider::GetFont(std::string name, TextStyle style, int size) {
  const auto id{std::make_tuple(name, style, size)};
  if (const auto it{fonts_.find(id)}; it != fonts_.end()) {
    return it->second;
  }
  return nullptr;
}
};  // namespace Pano
