// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_COLOR_H_
#define INCLUDE_PANO_COLOR_H_

#include <Pano/constants.h>
#include <SDL3/SDL.h>

#include <map>

namespace Pano {
namespace Color {
constexpr SDL_Color Transparent{0x0, 0x0, 0x0, 0x0};

constexpr SDL_Color Black{0x0, 0x0, 0x0, 0xFF};
constexpr SDL_Color White{0xFF, 0xFF, 0xFF, 0xFF};

constexpr SDL_Color Gray_1{0x10, 0x10, 0x10, 0xFF};
constexpr SDL_Color Gray_2{0x20, 0x20, 0x20, 0xFF};
constexpr SDL_Color Gray_3{0x30, 0x30, 0x30, 0xFF};
constexpr SDL_Color Gray_4{0x40, 0x40, 0x40, 0xFF};
constexpr SDL_Color Gray_5{0x50, 0x50, 0x50, 0xFF};
constexpr SDL_Color Gray_6{0x60, 0x60, 0x60, 0xFF};
constexpr SDL_Color Gray_7{0x70, 0x70, 0x70, 0xFF};
constexpr SDL_Color Gray_8{0x80, 0x80, 0x80, 0xFF};
constexpr SDL_Color Gray_9{0x90, 0x90, 0x90, 0xFF};
constexpr SDL_Color Gray_A{0xA0, 0xA0, 0xA0, 0xFF};
constexpr SDL_Color Gray_B{0xB0, 0xB0, 0xB0, 0xFF};
constexpr SDL_Color Gray_C{0xC0, 0xC0, 0xC0, 0xFF};
constexpr SDL_Color Gray_D{0xD0, 0xD0, 0xD0, 0xFF};
constexpr SDL_Color Gray_E{0xE0, 0xE0, 0xE0, 0xFF};
};  // namespace Color

class ColorProvider {
 public:
  ColorProvider() {}
  ~ColorProvider() {}

  ColorProvider(const ColorProvider&) = delete;
  ColorProvider& operator=(const ColorProvider&) = delete;
  ColorProvider(ColorProvider&&) = delete;
  ColorProvider& operator=(ColorProvider&&) = delete;

  SDL_Color GetColor(Significance significance, Condition condition,
                     Layer layer) const;
  void SetColor(Significance significance, Condition condition, Layer layer,
                SDL_Color color);

 protected:
  std::map<std::tuple<Significance, Condition, Layer>, SDL_Color> colors_;
  SDL_Color fallback_{0xFF, 0, 0, 0xFF};
};

class LightDarkSwitcher : public ColorProvider {
 public:
  LightDarkSwitcher(ColorProvider* l, ColorProvider* d) : light{l}, dark{d} {}
  ~LightDarkSwitcher() {}

  LightDarkSwitcher(const LightDarkSwitcher&) = delete;
  LightDarkSwitcher& operator=(const LightDarkSwitcher&) = delete;
  LightDarkSwitcher(LightDarkSwitcher&&) = delete;
  LightDarkSwitcher& operator=(LightDarkSwitcher&&) = delete;

  SDL_Color GetColor(Significance significance, Condition condition,
                     Layer layer) const;
  void SetDark(bool dark) { darkmode = dark; }

 protected:
  ColorProvider* light;
  ColorProvider* dark;
  bool darkmode{false};
};

};  // namespace Pano

#endif  // INCLUDE_PANO_COLOR_H_
