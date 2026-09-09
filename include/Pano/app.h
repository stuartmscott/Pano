// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_APP_H_
#define INCLUDE_PANO_APP_H_

#include <Pano/animation.h>
#include <Pano/color.h>
#include <Pano/font.h>
#include <Pano/icon.h>
#include <Pano/window.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <algorithm>
#include <map>
#include <string>
#include <vector>

namespace Pano {
class App {
 public:
  App();
  ~App();
  static App* current_;

  App(const App&) = delete;
  App& operator=(const App&) = delete;
  App(App&&) = delete;
  App& operator=(App&&) = delete;

  ColorProvider* GetColorProvider();
  FontProvider* GetFontProvider();
  IconProvider* GetIconProvider();

  void SetColorProvider(ColorProvider* provider);
  void SetFontProvider(FontProvider* provider);
  void SetIconProvider(IconProvider* provider);

  // SDL3;
  // - Properties
  // - Filesystem
  // - File Dialog
  // - Locale
  // - System Tray
  // - Clipboard

  void Start();
  bool Quit();
  std::function<bool()> OnQuitRequested{nullptr};

  void AddWindow(SDL_WindowID id, Window* window) { windows_[id] = window; }
  void RemoveWindow(SDL_WindowID id) { windows_.erase(id); }

  void AddAnimation(Animation* a) { animations_.push_back(a); }
  void RemoveAnimation(Animation* a) { std::erase(animations_, a); }

  void Handle(SDL_Event&);

 private:
  std::atomic_bool running_{true};
  ColorProvider* color_provider_{nullptr};
  FontProvider* font_provider_{nullptr};
  IconProvider* icon_provider_{nullptr};
  std::map<int, Window*> windows_;
  std::vector<Animation*> animations_;
};

SDL_WindowID GetWindowFromEvent(const SDL_Event& e);
};  // namespace Pano

#endif  // INCLUDE_PANO_APP_H_
