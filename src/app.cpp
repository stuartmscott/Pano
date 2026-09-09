// Copyright 2026 Stuart Scott
#include <Pano/app.h>
#include <Pano/color.h>
#include <Pano/constants.h>
#include <Pano/font.h>
#include <Pano/icon.h>
#include <Pano/log.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

namespace Pano {

App* App::current_{nullptr};

App::App() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    Error() << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
  }

  if (!TTF_Init()) {
    Error() << "Failed to initialize SDL_ttf: " << SDL_GetError() << std::endl;
  }

  current_ = this;
  Info() << "App Created" << std::endl;
}

App::~App() {
  running_ = false;
  if (const auto p{color_provider_}; p != nullptr) {
    delete p;
  }
  if (const auto p{icon_provider_}; p != nullptr) {
    delete p;
  }
  if (const auto p{font_provider_}; p != nullptr) {
    delete p;
  }
  TTF_Quit();
  SDL_Quit();
  Info() << "App Destroyed" << std::endl;
}

ColorProvider* App::GetColorProvider() {
  if (color_provider_ == nullptr) {
    Error() << "Missing Color Provider" << std::endl;
  }
  return color_provider_;
}

IconProvider* App::GetIconProvider() {
  if (icon_provider_ == nullptr) {
    Error() << "Missing Icon Provider" << std::endl;
  }
  return icon_provider_;
}

FontProvider* App::GetFontProvider() {
  if (font_provider_ == nullptr) {
    Error() << "Missing Font Provider" << std::endl;
  }
  return font_provider_;
}

void App::SetColorProvider(ColorProvider* provider) {
  if (const auto p{color_provider_}; p != nullptr) {
    delete p;
  }
  color_provider_ = provider;
}

void App::SetIconProvider(IconProvider* provider) {
  if (const auto p{icon_provider_}; p != nullptr) {
    delete p;
  }
  icon_provider_ = provider;
}

void App::SetFontProvider(FontProvider* provider) {
  if (const auto p{font_provider_}; p != nullptr) {
    delete p;
  }
  font_provider_ = provider;
}

void App::Start() {
  Info() << "App Started" << std::endl;

  SDL_Event e;
  SDL_zero(e);

  while (running_) {
    if (const auto e{std::string(SDL_GetError())}; !e.empty()) {
      Error() << "SDL_GetError: " << e << std::endl;
      SDL_ClearError();
    }

    while (SDL_WaitEventTimeout(&e, 10)) {
      Handle(e);
    }

    auto now{std::chrono::system_clock::now()};
    for (auto it{animations_.begin()}; it != animations_.end();) {
      if ((*it)->Tick(now)) {
        ++it;
      } else {
        it = animations_.erase(it);
      }
    }

    for (auto it{windows_.begin()}; it != windows_.end(); ++it) {
      if (it->second->IsVisible() && it->second->IsDirty()) {
        it->second->Draw();
      }
    }
  }
}

void App::Handle(SDL_Event& e) {
  if (e.type == SDL_EVENT_QUIT) {
    Info() << "App Quit Event" << std::endl;

    bool success{true};
    for (auto it{windows_.begin()}; success && it != windows_.end(); ++it) {
      success = it->second->Close();
    }

    if (success) {
      Quit();
    }
  } else {
    SDL_WindowID id(GetWindowFromEvent(e));
    if (id > 0) {
      if (const auto it{windows_.find(id)}; it != windows_.end()) {
        it->second->Handle(e);
      }
    }
  }
}

bool App::Quit() {
  if (OnQuitRequested) {
    if (!OnQuitRequested()) {
      return false;
    }
  }

  Info() << "App Quiting" << std::endl;
  running_ = false;

  return true;
}

SDL_WindowID GetWindowFromEvent(const SDL_Event& e) {
  switch (e.type) {
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
    case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
    case SDL_EVENT_WINDOW_EXPOSED:
    case SDL_EVENT_WINDOW_FOCUS_GAINED:
    case SDL_EVENT_WINDOW_FOCUS_LOST:
    case SDL_EVENT_WINDOW_HIDDEN:
    case SDL_EVENT_WINDOW_HIT_TEST:
    case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
    case SDL_EVENT_WINDOW_MAXIMIZED:
    case SDL_EVENT_WINDOW_MINIMIZED:
    case SDL_EVENT_WINDOW_MOUSE_ENTER:
    case SDL_EVENT_WINDOW_MOUSE_LEAVE:
    case SDL_EVENT_WINDOW_MOVED:
    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
    case SDL_EVENT_WINDOW_RESIZED:
    case SDL_EVENT_WINDOW_RESTORED:
    case SDL_EVENT_WINDOW_SHOWN:
      return e.window.windowID;
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
      return e.key.windowID;
    case SDL_EVENT_TEXT_EDITING:
      return e.edit.windowID;
    case SDL_EVENT_TEXT_EDITING_CANDIDATES:
      return e.edit_candidates.windowID;
    case SDL_EVENT_TEXT_INPUT:
      return e.text.windowID;
    case SDL_EVENT_CLIPBOARD_UPDATE:
      return 0;
    case SDL_EVENT_FINGER_DOWN:
    case SDL_EVENT_FINGER_UP:
    case SDL_EVENT_FINGER_CANCELED:
    case SDL_EVENT_FINGER_MOTION:
      return e.tfinger.windowID;
    case SDL_EVENT_MOUSE_MOTION:
      return e.motion.windowID;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
      return e.button.windowID;
    case SDL_EVENT_MOUSE_WHEEL:
      return e.wheel.windowID;
    case SDL_EVENT_PEN_PROXIMITY_IN:
    case SDL_EVENT_PEN_PROXIMITY_OUT:
      return e.pproximity.windowID;
    case SDL_EVENT_PEN_DOWN:
    case SDL_EVENT_PEN_UP:
      return e.ptouch.windowID;
    case SDL_EVENT_PEN_BUTTON_DOWN:
    case SDL_EVENT_PEN_BUTTON_UP:
      return e.pbutton.windowID;
    case SDL_EVENT_PEN_MOTION:
      return e.pmotion.windowID;
    case SDL_EVENT_PEN_AXIS:
      return e.paxis.windowID;
    case SDL_EVENT_DROP_FILE:
    case SDL_EVENT_DROP_TEXT:
    case SDL_EVENT_DROP_BEGIN:
    case SDL_EVENT_DROP_COMPLETE:
    case SDL_EVENT_DROP_POSITION:
      return e.drop.windowID;
    case SDL_EVENT_RENDER_TARGETS_RESET:
    case SDL_EVENT_RENDER_DEVICE_RESET:
    case SDL_EVENT_RENDER_DEVICE_LOST:
      return e.render.windowID;
    default:
      Error() << "Unrecognized event type: " << e.type << std::endl;
  }
  return 0;
}
};  // namespace Pano
