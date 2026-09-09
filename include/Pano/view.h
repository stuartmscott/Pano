// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_VIEW_H_
#define INCLUDE_PANO_VIEW_H_

#include <Pano/constants.h>
#include <Pano/geometry.h>
#include <SDL3/SDL.h>

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace Pano {
// Forward Declaration
class Window;

class View {
 public:
  View() {}
  virtual ~View();

  View(const View&) = delete;
  View& operator=(const View&) = delete;
  View(View&&) = delete;
  View& operator=(View&&) = delete;

  // Get State
  virtual bool IsDirty() const { return dirty_; }
  bool IsVisible() const { return visible_; }
  bool IsEnabled() const { return IsBitSet(condition_, Condition::Enabled); }
  Point GetPosition() const { return position_; }
  Size GetSize() const { return size_; }
  virtual Size GetMinimumSize() const { return {}; }
  virtual SDL_Color GetColor(Layer layer) const;
  Condition GetCondition() const { return condition_; }
  Alignment GetHorizontalAlignment() const { return horizontal_alignment_; }
  Alignment GetVerticalAlignment() const { return vertical_alignment_; }
  class Artist {
   public:
    explicit Artist(View* view) : view_(view) {}
    virtual ~Artist();

    virtual SDL_Texture* GetTexture() const { return texture_; }

    virtual void BeforeDraw(SDL_Renderer*);
    virtual void Draw(SDL_Renderer*);
    virtual void AfterDraw(SDL_Renderer*);

   protected:
    View* view_;
    SDL_Texture* texture_{nullptr};
    Size texture_size_{};
  };
  virtual Artist* GetArtist() { return artist_; }
  View* GetParent() const { return parent_; }
  Window* GetWindow() const { return window_; }
  virtual std::vector<View*> GetKeyboardableViews();
  virtual std::vector<View*> GetMouseableViews(Point);

  // Set State
  virtual void Redraw() {
    dirty_ = true;
    if (parent_ != nullptr) {
      parent_->Redraw();
    }
  }
  virtual void SetVisible(const bool v) {
    visible_ = v;
    Redraw();
  }
  virtual void SetPosition(const Point p) {
    position_.x = p.x;
    position_.y = p.y;
    position_.z = p.z;
  }
  virtual void SetSize(const Size s) {
    size_.width = s.width;
    size_.height = s.height;
    size_.depth = s.depth;
    Redraw();
  }
  void SetColor(const Layer layer, const SDL_Color color) {
    switch (layer) {
      case Layer::Background:
        background_color_ = color;
        background_color_overriden_ = true;
        break;
      case Layer::Foreground:
        foreground_color_ = color;
        foreground_color_overriden_ = true;
        break;
    }
    Redraw();
  }
  void ClearColorOverride(Layer layer) {
    switch (layer) {
      case Layer::Background:
        background_color_overriden_ = false;
        break;
      case Layer::Foreground:
        foreground_color_overriden_ = false;
        break;
    }
    Redraw();
  }
  virtual void SetCondition(const Condition condition) {
    condition_ = condition;
    Redraw();
  }
  virtual void SetSignificance(const Significance significance) {
    significance_ = significance;
    Redraw();
  }
  virtual void SetHorizontalAlignment(const Alignment alignment) {
    horizontal_alignment_ = alignment;
    Redraw();
  }
  virtual void SetVerticalAlignment(const Alignment alignment) {
    vertical_alignment_ = alignment;
    Redraw();
  }
  virtual void SetParent(View* parent) { parent_ = parent; }
  virtual void SetWindow(Window* window) { window_ = window; }

  // Event Handling
  std::function<void()> OnKeyboardFocusGained{nullptr};
  std::function<void()> OnKeyboardFocusLost{nullptr};
  std::function<void(SDL_KeyboardEvent&)> OnKeyboardEvent{nullptr};
  std::function<void(SDL_TextEditingEvent&)> OnTextEditingEvent{nullptr};
  std::function<void(SDL_TextInputEvent&)> OnTextInputEvent{nullptr};
  std::function<void(SDL_TouchFingerEvent&)> OnTouchFingerEvent{nullptr};
  std::function<void()> OnMouseFocusGained{nullptr};
  std::function<void()> OnMouseFocusLost{nullptr};
  std::function<void(SDL_MouseButtonEvent&)> OnMouseButtonEvent{nullptr};
  std::function<void(SDL_MouseMotionEvent&)> OnMouseMotionEvent{nullptr};
  std::function<void(SDL_MouseWheelEvent&)> OnMouseWheelEvent{nullptr};

  virtual bool HandleKeyboardFocusGained() {
    if (const auto h{OnKeyboardFocusGained}; h != nullptr) {
      has_keyboard_focus_ = true;
      h();
      return true;
    }
    return false;
  }
  virtual bool HandleKeyboardFocusLost() {
    has_keyboard_focus_ = false;
    if (const auto h{OnKeyboardFocusLost}; h != nullptr) {
      h();
      return true;
    }
    return false;
  }
  virtual bool HandleKeyboardEvent(SDL_KeyboardEvent& e) {
    if (const auto h{OnKeyboardEvent}; h != nullptr) {
      h(e);
      return true;
    }
    return false;
  }
  virtual bool HandleTextEditingEvent(SDL_TextEditingEvent& e) {
    if (const auto h{OnTextEditingEvent}; h != nullptr) {
      h(e);
      return true;
    }
    return false;
  }
  virtual bool HandleTextInputEvent(SDL_TextInputEvent& e) {
    if (const auto h{OnTextInputEvent}; h != nullptr) {
      h(e);
      return true;
    }
    return false;
  }
  virtual bool HandleTouchFingerEvent(SDL_TouchFingerEvent& e) {
    if (const auto h{OnTouchFingerEvent}; h != nullptr) {
      h(e);
      return true;
    }
    return false;
  }
  virtual bool HandleMouseFocusGained() {
    if (const auto h{OnMouseFocusGained}; h != nullptr) {
      has_mouse_focus_ = true;
      h();
      return true;
    }
    return false;
  }
  virtual bool HandleMouseFocusLost() {
    has_mouse_focus_ = false;
    if (const auto h{OnMouseFocusLost}; h != nullptr) {
      h();
      return true;
    }
    return false;
  }
  virtual bool HandleMouseButtonEvent(SDL_MouseButtonEvent& e) {
    if (const auto h{OnMouseButtonEvent}; h != nullptr) {
      h(e);
      return true;
    }
    return false;
  }
  virtual bool HandleMouseMotionEvent(SDL_MouseMotionEvent& e) {
    if (const auto h{OnMouseMotionEvent}; h != nullptr) {
      h(e);
      return true;
    }
    return false;
  }
  virtual bool HandleMouseWheelEvent(SDL_MouseWheelEvent& e) {
    if (const auto h{OnMouseWheelEvent}; h != nullptr) {
      h(e);
      return true;
    }
    return false;
  }

 protected:
  bool dirty_{true};
  bool visible_{true};
  bool has_keyboard_focus_{false};
  bool has_mouse_focus_{false};
  Point position_{};
  Size size_{};
  SDL_Color background_color_{};
  SDL_Color foreground_color_{};
  bool background_color_overriden_{false};
  bool foreground_color_overriden_{false};
  Condition condition_{Condition::Enabled};
  Significance significance_{Significance::Normal};
  Alignment horizontal_alignment_{Alignment::Center};
  Alignment vertical_alignment_{Alignment::Center};
  Artist* artist_{nullptr};
  View* parent_{nullptr};
  Window* window_{nullptr};
};

std::vector<View*> GetSortedMouseableViews(View* v, Point p);
void DrawView(SDL_Renderer* renderer, SDL_Texture* texture, View* view);
};  // namespace Pano

#endif  // INCLUDE_PANO_VIEW_H_
