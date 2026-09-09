// Copyright 2026 Stuart Scott
#include <Pano/app.h>
#include <Pano/log.h>
#include <Pano/window.h>
#include <SDL3/SDL.h>

#include <string>

namespace Pano {

Window::Window(std::string title, uint32_t width, uint32_t height)
    : size_(width, height) {
  window_ = SDL_CreateWindow(title.c_str(), width, height,
                             SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
  if (window_ == nullptr) {
    Error() << "Failed to create window: " << SDL_GetError() << std::endl;
    return;
  }

  id_ = SDL_GetWindowID(window_);

  App::current_->AddWindow(id_, this);

  renderer_ = SDL_CreateRenderer(window_, nullptr);
  if (renderer_ == nullptr) {
    Error() << "Failed to create renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window_);
    window_ = nullptr;
    return;
  }
}

Window::~Window() { Destroy(); }

void Window::Destroy() {
  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }

  if (window_ != nullptr) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;

    App::current_->RemoveWindow(id_);
  }

  if (snapshot_ != nullptr) {
    SDL_DestroySurface(snapshot_);
    snapshot_ = nullptr;
  }
}

bool Window::IsDirty() const {
  if (!IsVisible()) {
    return false;
  }

  if (const auto v{content_}; v != nullptr && v->IsDirty()) {
    return true;
  }

  if (const auto v{overlay_}; v != nullptr && v->IsDirty()) {
    return true;
  }

  return false;
}

bool Window::IsVisible() const {
  if (window_ != nullptr) {
    return (SDL_GetWindowFlags(window_) & SDL_WINDOW_HIDDEN) == 0;
  }

  return false;
}

bool Window::IsMinimized() const {
  if (window_ != nullptr) {
    return SDL_GetWindowFlags(window_) & SDL_WINDOW_MINIMIZED;
  }

  return false;
}

bool Window::IsMaximized() const {
  if (window_ != nullptr) {
    return SDL_GetWindowFlags(window_) & SDL_WINDOW_MAXIMIZED;
  }

  return false;
}

bool Window::IsFullscreen() const {
  if (window_ != nullptr) {
    return SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN;
  }

  return false;
}

void run_on_main(SDL_MainThreadCallback callback, void* userdata) {
  if (!SDL_RunOnMainThread(callback, userdata, true)) {
    Error() << "Failed to run callback on main thread: " << SDL_GetError()
            << std::endl;
  }
}

void SDLCALL hide_window_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_HideWindow(w);
  }
}

void SDLCALL show_window_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_ShowWindow(w);
  }
}

void Window::SetVisible(bool visible) {
  if (visible) {
    run_on_main(show_window_callback, this);
  } else {
    run_on_main(hide_window_callback, this);
  }
}

void SDLCALL set_maximized_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_MaximizeWindow(w);
  }
}

void Window::SetMaximized() { run_on_main(set_maximized_callback, this); }

void SDLCALL set_minimized_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_MinimizeWindow(w);
  }
}

void Window::SetMinimized() { run_on_main(set_minimized_callback, this); }

void SDLCALL restored_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_RestoreWindow(w);
  }
}

void Window::SetRestored() { run_on_main(restored_callback, this); }

void SDLCALL enter_fullscreen_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_SetWindowFullscreen(w, SDL_WINDOW_FULLSCREEN);
  }
}

void SDLCALL exit_fullscreen_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_SetWindowFullscreen(w, 0);
  }
}

void Window::SetFullscreen(bool fullscreen) {
  if (fullscreen) {
    run_on_main(enter_fullscreen_callback, this);
  } else {
    run_on_main(exit_fullscreen_callback, this);
  }
}

void SDLCALL set_title_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_SetWindowTitle(w, window->requested_title_.c_str());
  }
}

void Window::SetTitle(std::string title) {
  requested_title_ = title;
  run_on_main(set_title_callback, this);
}

void SDLCALL resized_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};
  if (const auto w{window->window_}; w != nullptr) {
    SDL_SetWindowSize(w, window->requested_size_.width,
                      window->requested_size_.height);
  }
}

void Window::SetSize(Size size) {
  requested_size_ = size;
  run_on_main(resized_callback, this);
}

void Window::SetContent(View* v) {
  content_ = v;
  content_->SetWindow(this);
  content_->SetSize(size_);
}

void Window::SetOverlay(View* v) {
  overlay_ = v;
  overlay_->SetWindow(this);
}

void Window::SetKeyboardFocusedView(View* v) {
  if (v == keyboard_focus_holder_) {
    return;
  }
  if (const auto h{keyboard_focus_holder_}; h != nullptr) {
    h->HandleKeyboardFocusLost();
  }
  if (v->HandleKeyboardFocusGained()) {
    keyboard_focus_holder_ = v;
  }
}

void Window::SetMouseFocusedView(View* v) {
  if (v == mouse_focus_holder_) {
    return;
  }
  if (const auto h{mouse_focus_holder_}; h != nullptr) {
    h->HandleMouseFocusLost();
  }
  if (v->HandleMouseFocusGained()) {
    mouse_focus_holder_ = v;
  }
}

void Window::Handle(SDL_Event& e) {
  switch (e.type) {
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
      if (Close()) {
        Destroy();
      }
      break;
    }
    case SDL_EVENT_WINDOW_DISPLAY_CHANGED: {
      break;
    }
    case SDL_EVENT_WINDOW_EXPOSED: {
      Draw();
      break;
    }
    case SDL_EVENT_WINDOW_FOCUS_GAINED: {
      has_keyboard_focus = true;
      if (const auto v{keyboard_focus_holder_}; v != nullptr) {
        if (!v->HandleKeyboardFocusGained()) {
          keyboard_focus_holder_ = nullptr;
        }
      }
      if (keyboard_focus_holder_ == nullptr) {
        handle_keyboard_focus_gained(overlay_);
      }
      if (keyboard_focus_holder_ == nullptr) {
        handle_keyboard_focus_gained(content_);
      }
      break;
    }
    case SDL_EVENT_WINDOW_FOCUS_LOST: {
      has_keyboard_focus = false;
      if (const auto v{keyboard_focus_holder_}; v != nullptr) {
        v->HandleKeyboardFocusLost();
      }
      break;
    }
    case SDL_EVENT_WINDOW_HIDDEN: {
      break;
    }
    case SDL_EVENT_WINDOW_HIT_TEST: {
      break;
    }
    case SDL_EVENT_WINDOW_ICCPROF_CHANGED: {
      break;
    }
    case SDL_EVENT_WINDOW_MAXIMIZED: {
      break;
    }
    case SDL_EVENT_WINDOW_MINIMIZED: {
      break;
    }
    case SDL_EVENT_WINDOW_MOUSE_ENTER: {
      has_mouse_focus = true;
      if (const auto h{mouse_focus_holder_}; h != nullptr) {
        h->HandleMouseFocusGained();
      }
      break;
    }
    case SDL_EVENT_WINDOW_MOUSE_LEAVE: {
      has_mouse_focus = false;
      if (const auto h{mouse_focus_holder_}; h != nullptr) {
        h->HandleMouseFocusLost();
      }
      break;
    }
    case SDL_EVENT_WINDOW_MOVED: {
      break;
    }
    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
    case SDL_EVENT_WINDOW_RESIZED: {
      size_.width = e.window.data1;
      size_.height = e.window.data2;
      if (const auto c{content_}; c != nullptr) {
        c->SetSize(size_);
      }
      if (const auto o{overlay_}; o != nullptr) {
        o->SetSize(size_);
      }
      break;
    }
    case SDL_EVENT_WINDOW_RESTORED: {
      break;
    }
    case SDL_EVENT_WINDOW_SHOWN: {
      break;
    }
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP: {
      if (const auto v{keyboard_focus_holder_};
          v != nullptr && v->IsVisible()) {
        v->HandleKeyboardEvent(e.key);
      }
      break;
    }
    case SDL_EVENT_TEXT_EDITING: {
      if (const auto v{keyboard_focus_holder_};
          v != nullptr && v->IsVisible()) {
        v->HandleTextEditingEvent(e.edit);
      }
      break;
    }
    case SDL_EVENT_TEXT_INPUT: {
      if (const auto v{keyboard_focus_holder_};
          v != nullptr && v->IsVisible()) {
        v->HandleTextInputEvent(e.text);
      }
      break;
    }
    case SDL_EVENT_CLIPBOARD_UPDATE: {
      break;
    }
    case SDL_EVENT_FINGER_DOWN:
    case SDL_EVENT_FINGER_UP:
    case SDL_EVENT_FINGER_CANCELED:
    case SDL_EVENT_FINGER_MOTION: {
      handle_touchfinger_event(overlay_, e.tfinger) ||
          handle_touchfinger_event(content_, e.tfinger);
      break;
    }
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP: {
      handle_mouse_button_event(overlay_, e.button) ||
          handle_mouse_button_event(content_, e.button);
      break;
    }
    case SDL_EVENT_MOUSE_MOTION: {
      if (!handle_mouse_motion_event(overlay_, e.motion) &&
          !handle_mouse_motion_event(content_, e.motion)) {
        if (const auto h{mouse_focus_holder_}; h != nullptr) {
          h->HandleMouseFocusLost();
          mouse_focus_holder_ = nullptr;
        }
      }
      break;
    }
    case SDL_EVENT_MOUSE_WHEEL: {
      handle_mouse_wheel_event(overlay_, e.wheel) ||
          handle_mouse_wheel_event(content_, e.wheel);
      break;
    }
    default: {
      Info() << "Unhandled event: " << e.type << std::endl;
    }
  }
}

bool Window::Close() {
  if (OnCloseRequested) {
    return OnCloseRequested();
  }

  return true;
}

void SDLCALL snapshot_callback(void* userdata) {
  const auto window{static_cast<Window*>(userdata)};

  if (window->snapshot_ != nullptr) {
    SDL_DestroySurface(window->snapshot_);
    window->snapshot_ = nullptr;
  }

  window->Draw();

  window->snapshot_ = SDL_RenderReadPixels(window->renderer_, nullptr);
}

void Window::Snapshot(std::string filename) {
  run_on_main(snapshot_callback, this);
  if (snapshot_ == nullptr) {
    Error() << "Failed to read pixels: " << SDL_GetError() << std::endl;
  } else {
    if (!SDL_SavePNG(snapshot_, filename.c_str())) {
      Error() << "Failed to save file: " << SDL_GetError() << std::endl;
    }
    SDL_DestroySurface(snapshot_);
  }
}

void Window::Draw() {
  if (renderer_ == nullptr) {
    return;
  }

  if (!SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0)) {
    Error() << "Failed to set draw color: " << SDL_GetError() << std::endl;
  }

  if (!SDL_RenderClear(renderer_)) {
    Error() << "Failed to clear: " << SDL_GetError() << std::endl;
  }

  DrawView(renderer_, nullptr, content_);
  DrawView(renderer_, nullptr, overlay_);

  SDL_RenderPresent(renderer_);
}

bool Window::handle_keyboard_focus_gained(View* view) {
  if (view != nullptr && view->IsVisible() && view->IsEnabled()) {
    for (const auto v : view->GetKeyboardableViews()) {
      if (v->HandleKeyboardFocusGained()) {
        keyboard_focus_holder_ = v;
        return true;
      }
    }
  }
  return false;
}

bool Window::handle_touchfinger_event(View* view, SDL_TouchFingerEvent e) {
  const auto x{e.x * size_.width};
  const auto y{e.y * size_.height};
  if (view != nullptr && view->IsVisible() && view->IsEnabled()) {
    for (const auto v : GetSortedMouseableViews(view, {x, y})) {
      if (v->IsEnabled() && v->HandleTouchFingerEvent(e)) {
        return true;
      }
    }
  }
  return false;
}

bool Window::handle_mouse_button_event(View* view, SDL_MouseButtonEvent e) {
  const auto x{e.x};
  const auto y{e.y};
  if (view != nullptr && view->IsVisible() && view->IsEnabled()) {
    for (const auto v : GetSortedMouseableViews(view, {x, y})) {
      if (v->IsEnabled() && v->HandleMouseButtonEvent(e)) {
        return true;
      }
    }
  }
  return false;
}

bool Window::handle_mouse_motion_event(View* view, SDL_MouseMotionEvent e) {
  const auto x{e.x};
  const auto y{e.y};
  if (view != nullptr && view->IsVisible() && view->IsEnabled()) {
    for (const auto v : GetSortedMouseableViews(view, {x, y})) {
      if (!v->IsEnabled()) {
        continue;
      }
      if (v == mouse_focus_holder_ && v->HandleMouseMotionEvent(e)) {
        return true;
      } else if (v->HandleMouseFocusGained() && v->HandleMouseMotionEvent(e)) {
        if (const auto h{mouse_focus_holder_}; h != nullptr) {
          h->HandleMouseFocusLost();
        }
        mouse_focus_holder_ = v;
        return true;
      }
    }
  }
  return false;
}

bool Window::handle_mouse_wheel_event(View* view, SDL_MouseWheelEvent e) {
  const auto x{e.mouse_x};
  const auto y{e.mouse_y};
  if (view != nullptr && view->IsVisible() && view->IsEnabled()) {
    for (const auto v : GetSortedMouseableViews(view, {x, y})) {
      if (v->IsEnabled() && v->HandleMouseWheelEvent(e)) {
        return true;
      }
    }
  }
  return false;
}
};  // namespace Pano
