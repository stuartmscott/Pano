// Copyright 2026 Stuart Scott
#ifndef FONT_NOTO_INCLUDE_PANONOTOSANS_PROVIDER_H_
#define FONT_NOTO_INCLUDE_PANONOTOSANS_PROVIDER_H_

#include <Pano/font.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <utility>
#include <vector>

class NotoSansFontProvider : public Pano::FontProvider {
 public:
  NotoSansFontProvider();
  ~NotoSansFontProvider() {}

  NotoSansFontProvider(const NotoSansFontProvider&) = delete;
  NotoSansFontProvider& operator=(const NotoSansFontProvider&) = delete;
  NotoSansFontProvider(NotoSansFontProvider&&) = delete;
  NotoSansFontProvider& operator=(NotoSansFontProvider&&) = delete;

  std::string GetFontName() const override;
  Pano::Font* GetFont(std::string name, Pano::TextStyle style,
                      int size) override;

 private:
  std::vector<std::pair<std::string, Pano::TextStyle>> fallbacks_;
};

TTF_Font* LoadNotoSansFont(std::string name, Pano::TextStyle style, int size);

NotoSansFontProvider* CreateNotoSansProvider();

#endif  // FONT_NOTO_INCLUDE_PANONOTOSANS_PROVIDER_H_
