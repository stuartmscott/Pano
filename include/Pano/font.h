// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_FONT_H_
#define INCLUDE_PANO_FONT_H_

#include <Pano/constants.h>
#include <Pano/geometry.h>
#include <Pano/log.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace Pano {
class Font {
 public:
  explicit Font(TTF_Font* font) : font_(font) {}
  ~Font() {
    for (const auto& [k, v] : textures_) {
      SDL_DestroyTexture(v.first);
    }
    textures_.clear();
    TTF_CloseFont(font_);
  }

  void AddFallback(Font* fallback) {
    if (!TTF_AddFallbackFont(font_, fallback->font_)) {
      Error() << "Failed to add fallback font: " << SDL_GetError() << std::endl;
    }
  }

  int GetAdvance(char32_t c);
  void GetMetrics(char32_t c, int* min_x, int* max_x, int* min_y, int* max_y,
                  int* advance);
  int GetKerning(char32_t a, char32_t b);
  int GetAscent() { return TTF_GetFontAscent(font_); }
  int GetDescent() { return TTF_GetFontDescent(font_); }
  int GetHeight() { return TTF_GetFontHeight(font_); }
  int GetLineSkip() { return TTF_GetFontLineSkip(font_); }

  void Draw(SDL_Renderer* renderer, std::string string, Point position,
            SDL_Color color);

 private:
  std::pair<SDL_Texture*, Size> get_texture(SDL_Renderer* renderer,
                                            std::string string,
                                            SDL_Color color);
  TTF_Font* font_;
  std::map<std::tuple<std::string, int, int, int, int>,
           std::pair<SDL_Texture*, Size>>
      textures_;
};

class FontProvider {
 public:
  FontProvider() {}
  virtual ~FontProvider();

  FontProvider(const FontProvider&) = delete;
  FontProvider& operator=(const FontProvider&) = delete;
  FontProvider(FontProvider&&) = delete;
  FontProvider& operator=(FontProvider&&) = delete;

  virtual std::string GetFontName() const = 0;
  virtual Font* GetFont(std::string name, TextStyle style, int size);

 protected:
  std::map<std::tuple<std::string, TextStyle, int>, Font*> fonts_;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_FONT_H_
