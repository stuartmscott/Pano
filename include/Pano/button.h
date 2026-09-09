// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_BUTTON_H_
#define INCLUDE_PANO_BUTTON_H_

#include <Pano/constants.h>
#include <Pano/edge.h>
#include <Pano/frame.h>
#include <Pano/geometry.h>
#include <Pano/text.h>
#include <Pano/view.h>
#include <SDL3/SDL.h>

#include <map>
#include <string>
#include <utility>

namespace Pano {
class Button : public View {
 public:
  Button() : View() { setup(); }
  explicit Button(std::string text)
      : View(), text_view_(text), has_text_(true) {
    setup();
  }
  explicit Button(Icon icon) : View(), icon_view_(icon), has_icon_(true) {
    setup();
  }
  Button(std::string text, Icon icon)
      : View(),
        text_view_(text),
        icon_view_(icon),
        has_text_(true),
        has_icon_(true) {
    setup();
  }
  Button(std::string text, std::function<void()> on_pressed)
      : View(), OnPressed(on_pressed), text_view_(text), has_text_(true) {
    setup();
  }
  Button(Icon icon, std::function<void()> on_pressed)
      : View(), OnPressed(on_pressed), icon_view_(icon), has_icon_(true) {
    setup();
  }
  Button(std::string text, Icon icon, std::function<void()> on_pressed)
      : View(),
        OnPressed(on_pressed),
        text_view_(text),
        icon_view_(icon),
        has_text_(true),
        has_icon_(true) {
    setup();
  }

  Button(const Button&) = delete;
  Button& operator=(const Button&) = delete;
  Button(Button&&) = delete;
  Button& operator=(Button&&) = delete;

  // Get State
  bool IsDirty() const override { return frame_.IsDirty(); }
  Artist* GetArtist() override { return frame_.GetArtist(); }
  Size GetMinimumSize() const override { return frame_.GetMinimumSize(); }
  const TextView* GetTextView() const { return &text_view_; }
  const IconView* GetIconView() const { return &icon_view_; }

  // Set State
  void Redraw() override {
    frame_.Redraw();
    View::Redraw();
  }
  void SetVisible(const bool v) override {
    frame_.SetVisible(v);
    View::SetVisible(v);
  }
  void SetPosition(const Point p) override {
    frame_.SetPosition(p);
    View::SetPosition(p);
  }
  void SetSize(const Size s) override {
    frame_.SetSize(s);
    View::SetSize(s);
  }
  void SetCondition(const Condition condition) override {
    frame_.SetCondition(condition);
    layout_.SetCondition(condition);
    text_view_.SetCondition(condition);
    icon_view_.SetCondition(condition);
    View::SetCondition(condition);
  }
  void SetSignificance(const Significance significance) override {
    frame_.SetSignificance(significance);
    layout_.SetSignificance(significance);
    text_view_.SetSignificance(significance);
    icon_view_.SetSignificance(significance);
    View::SetSignificance(significance);
  }
  void SetHorizontalAlignment(const Alignment alignment) override {
    frame_.SetHorizontalAlignment(alignment);
    layout_.SetHorizontalAlignment(alignment);
    text_view_.SetHorizontalAlignment(alignment);
    icon_view_.SetHorizontalAlignment(alignment);
    View::SetHorizontalAlignment(alignment);
  }
  void SetVerticalAlignment(const Alignment alignment) override {
    frame_.SetVerticalAlignment(alignment);
    layout_.SetVerticalAlignment(alignment);
    text_view_.SetVerticalAlignment(alignment);
    icon_view_.SetVerticalAlignment(alignment);
    View::SetVerticalAlignment(alignment);
  }
  void SetTextAlignment(const TextAlignment alignment) {
    text_view_.SetTextAlignment(alignment);
    Redraw();
  }
  void SetTextTruncation(const TextTruncation truncation) {
    text_view_.SetTextTruncation(truncation);
    Redraw();
  }
  void SetTextWrap(const TextWrap wrap) {
    text_view_.SetTextWrap(wrap);
    Redraw();
  }
  void SetTextStyle(const TextStyle style) {
    text_view_.SetTextStyle(style);
    Redraw();
  }
  void SetTextSize(const int size) {
    text_view_.SetTextSize(size);
    Redraw();
  }
  void SetText(const std::string text) {
    text_view_.SetText(text);
    if (!text.empty()) {
      has_text_ = true;
      layout_.ClearViews();
      layout_.SetView(Location::Center, &text_view_);
      if (has_icon_) {
        layout_.SetView(icon_location_, &icon_view_);
      }
    }
    Redraw();
  }
  void SetIcon(const Icon icon) {
    icon_view_.SetIcon(icon);
    has_icon_ = (icon != Icon::None);
    Redraw();
  }
  void SetIconLocation(const Location location);
  void SetParent(View* p) override {
    frame_.SetParent(p);
    View::SetParent(p);
  }
  void SetWindow(Window* w) override {
    frame_.SetWindow(w);
    View::SetWindow(w);
  }

  void ClearText() {
    text_view_.ClearText();
    has_text_ = false;
    layout_.ClearViews();
    if (has_icon_) {
      layout_.SetView(icon_location_, &icon_view_);
    }
  }
  void ClearIcon() {
    icon_view_.ClearIcon();
    has_icon_ = false;
    layout_.ClearViews();
    if (has_text_) {
      layout_.SetView(Location::Center, &text_view_);
    }
  }

  // Event Handling
  bool HandleTouchFingerEvent(SDL_TouchFingerEvent& e) override;
  bool HandleMouseFocusGained() override;
  bool HandleMouseFocusLost() override;
  bool HandleMouseButtonEvent(SDL_MouseButtonEvent& e) override;
  bool HandleMouseMotionEvent(SDL_MouseMotionEvent& e) override;

  std::function<void()> OnPressed{nullptr};
  std::function<void()> OnReleased{nullptr};

 private:
  void setup();

  FocusFrame frame_;
  EdgeLayout layout_;
  TextView text_view_;
  IconView icon_view_;
  Location icon_location_{Location::Top};
  bool has_text_{false};
  bool has_icon_{false};
};
};  // namespace Pano

#endif  // INCLUDE_PANO_BUTTON_H_
