// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_WINDOW_H_
#define INCLUDE_PANO_WINDOW_H_

#include <Pano/constants.h>
#include <Pano/geometry.h>
#include <Pano/view.h>
#include <SDL3/SDL.h>

#include <string>
#include <utility>

namespace Pano {
class Window {
 public:
  explicit Window(std::string title)
      : Window(title, WindowWidth, WindowHeight) {}
  Window(std::string title, uint32_t width, uint32_t height);
  ~Window();
  void Destroy();

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(Window&&) = delete;

  // Get State
  bool IsDirty() const;
  bool IsVisible() const;
  bool IsMinimized() const;
  bool IsMaximized() const;
  bool IsFullscreen() const;
  Size GetSize() const { return size_; }
  View* GetContent() const { return content_; }
  View* GetOverlay() const { return overlay_; }

  // Set State
  void SetVisible(bool visible);
  void SetMinimized();
  void SetMaximized();
  void SetRestored();
  void SetFullscreen(bool);
  void SetTitle(std::string title);
  void SetSize(Size size);
  void SetContent(View* v);
  void SetOverlay(View* v);
  void SetKeyboardFocusedView(View* v);
  void SetMouseFocusedView(View* v);

  // Event Handling
  void Handle(SDL_Event&);
  bool Close();
  std::function<bool()> OnCloseRequested{nullptr};

  // Rendering
  void Snapshot(std::string filename);
  void Draw();

  SDL_Window* window_{nullptr};
  SDL_Renderer* renderer_{nullptr};
  SDL_Surface* snapshot_{nullptr};
  std::string requested_title_;
  Size requested_size_{};

 private:
  bool handle_keyboard_focus_gained(View*);
  bool handle_touchfinger_event(View*, SDL_TouchFingerEvent);
  bool handle_mouse_button_event(View*, SDL_MouseButtonEvent);
  bool handle_mouse_motion_event(View*, SDL_MouseMotionEvent);
  bool handle_mouse_wheel_event(View*, SDL_MouseWheelEvent);

  uint32_t id_{0};
  Size size_{};
  View* content_{nullptr};
  View* overlay_{nullptr};
  View* mouse_focus_holder_{nullptr};
  View* keyboard_focus_holder_{nullptr};
  bool has_mouse_focus{false};
  bool has_keyboard_focus{false};
};
};  // namespace Pano

#endif  // INCLUDE_PANO_WINDOW_H_
