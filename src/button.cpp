// Copyright 2026 Stuart Scott
#include <Pano/button.h>
#include <Pano/constants.h>
#include <Pano/log.h>
#include <SDL3/SDL.h>

namespace Pano {

void Button::setup() {
  text_view_.SetParent(this);
  icon_view_.SetParent(this);
  SetHorizontalAlignment(Alignment::Center);
  SetVerticalAlignment(Alignment::Center);
  SetTextAlignment(TextAlignment::Center);
  if (has_text_) {
    layout_.SetView(Location::Center, &text_view_);
  }
  if (has_icon_) {
    layout_.SetView(icon_location_, &icon_view_);
  }
  frame_.SetView(&layout_);
}

void Button::SetIconLocation(Location location) {
  if (location != Location::Center) {
    icon_location_ = location;
    layout_.ClearViews();
    if (has_text_) {
      layout_.SetView(Location::Center, &text_view_);
    }
    if (has_icon_) {
      layout_.SetView(icon_location_, &icon_view_);
    }
    Redraw();
  }
}

bool Button::HandleTouchFingerEvent(SDL_TouchFingerEvent& e) {
  if (!IsEnabled()) {
    return false;
  }
  View::HandleTouchFingerEvent(e);
  if (e.type == SDL_EVENT_FINGER_DOWN) {
    if (const auto h{OnReleased}; h != nullptr) {
      h();
    }
  } else if (e.type == SDL_EVENT_FINGER_UP) {
    if (const auto h{OnPressed}; h != nullptr) {
      h();
    }
  }
  return true;
}

bool Button::HandleMouseFocusGained() {
  if (!IsEnabled()) {
    return false;
  }
  SetCondition(SetBit(condition_, Condition::Focused));
  View::HandleMouseFocusGained();
  return true;
}

bool Button::HandleMouseFocusLost() {
  if (!IsEnabled()) {
    return false;
  }
  SetCondition(ClearBit(condition_, Condition::Activated | Condition::Focused));
  View::HandleMouseFocusLost();
  return true;
}

bool Button::HandleMouseButtonEvent(SDL_MouseButtonEvent& e) {
  if (!IsEnabled()) {
    return false;
  }
  View::HandleMouseButtonEvent(e);
  if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    SetCondition(SetBit(condition_, Condition::Activated));
  } else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
    SetCondition(ClearBit(condition_, Condition::Activated));
  }
  if (e.which != SDL_TOUCH_MOUSEID) {
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      if (const auto h{OnPressed}; h != nullptr) {
        h();
      }
    } else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
      if (const auto h{OnReleased}; h != nullptr) {
        h();
      }
    }
  }
  return true;
}

bool Button::HandleMouseMotionEvent(SDL_MouseMotionEvent& e) {
  if (!IsEnabled()) {
    return false;
  }
  View::HandleMouseMotionEvent(e);
  return true;
}
};  // namespace Pano
