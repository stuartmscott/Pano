// Copyright 2026 Stuart Scott
#include <Pano/font.h>
#include <Pano/log.h>
#include <PanoNotoSans/notosans_bold.h>
#include <PanoNotoSans/notosans_bolditalic.h>
#include <PanoNotoSans/notosans_italic.h>
#include <PanoNotoSans/notosans_regular.h>
#include <PanoNotoSans/notosansmath_regular.h>
#include <PanoNotoSans/provider.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <sstream>
#include <string>
#include <utility>

using namespace Pano;

NotoSansFontProvider::NotoSansFontProvider()
    : FontProvider(), fallbacks_{{"NotoSansMath", TextStyle::Regular}} {}

std::string NotoSansFontProvider::GetFontName() const { return "NotoSans"; }

Font* NotoSansFontProvider::GetFont(std::string name, TextStyle style,
                                    int size) {
  Font* font{FontProvider::GetFont(name, style, size)};
  if (font != nullptr) {
    return font;
  }

  bool is_fallback{false};
  for (const auto& f : fallbacks_) {
    if (name == f.first && style == f.second) {
      is_fallback = true;
      break;
    }
  }

  TTF_Font* f{LoadNotoSansFont(name, style, size)};
  if (f != nullptr) {
    font = new Font(f);

    if (!is_fallback) {
      for (const auto& b : fallbacks_) {
        const auto fb{GetFont(b.first, b.second, size)};
        if (fb == nullptr) {
          Error() << "Failed to load fallback font: " << SDL_GetError()
                  << std::endl;
        } else {
          font->AddFallback(fb);
        }
      }
    }

    const auto id{std::make_tuple(name, style, size)};
    fonts_[id] = font;
  }
  return font;
}

TTF_Font* LoadNotoSansFont(std::string name, TextStyle style, int size) {
  SDL_IOStream* stream{nullptr};
  if (name == "NotoSans") {
    if ((style & TextStyle::BoldItalic) == TextStyle::BoldItalic) {
      stream = SDL_IOFromConstMem(notosans_bolditalic, notosans_bolditalic_len);
    } else if ((style & TextStyle::Bold) == TextStyle::Bold) {
      stream = SDL_IOFromConstMem(notosans_bold, notosans_bold_len);
    } else if ((style & TextStyle::Italic) == TextStyle::Italic) {
      stream = SDL_IOFromConstMem(notosans_italic, notosans_italic_len);
    } else {
      stream = SDL_IOFromConstMem(notosans_regular, notosans_regular_len);
    }
  } else if (name == "NotoSansMath") {
    stream = SDL_IOFromConstMem(notosansmath_regular, notosansmath_regular_len);
  }
  if (stream == nullptr) {
    Error() << "Unrecognized font: " << name << ' ' << ToString(style) << ": "
            << SDL_GetError() << std::endl;
    return nullptr;
  }
  TTF_Font* f{TTF_OpenFontIO(stream, true, size)};
  if (f == nullptr) {
    Error() << "Failed to open font: " << name << ' ' << ToString(style) << ": "
            << SDL_GetError() << std::endl;
  }
  return f;
}

NotoSansFontProvider* CreateNotoSansProvider() {
  return new NotoSansFontProvider();
}
