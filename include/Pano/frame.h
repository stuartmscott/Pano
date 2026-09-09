// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_FRAME_H_
#define INCLUDE_PANO_FRAME_H_

#include <Pano/color.h>
#include <Pano/geometry.h>
#include <Pano/view.h>

#include <map>
#include <utility>
#include <vector>

namespace Pano {
/* Frame encompasses a single view with a customizable margin, border, and
 * padding.*/
class Frame : public View {
 public:
  Frame() : View() {}
  explicit Frame(View* v) : Frame() { SetView(v); }

  Frame(const Frame&) = delete;
  Frame& operator=(const Frame&) = delete;
  Frame(Frame&&) = delete;
  Frame& operator=(Frame&&) = delete;

  // Get State
  Size GetMinimumSize() const override;
  class FrameArtist : public Artist {
   public:
    explicit FrameArtist(Frame* view) : Artist(view) {}

    void Draw(SDL_Renderer*) override;

   private:
    void draw_border(SDL_Renderer*, Point p, Size s, SDL_Color c);
  };

  Artist* GetArtist() override {
    if (artist_ == nullptr) {
      artist_ = new FrameArtist(this);
    }
    return View::GetArtist();
  }
  std::vector<View*> GetKeyboardableViews() override;
  std::vector<View*> GetMouseableViews(Point p) override;

  // Set State
  void SetSize(const Size s) override;
  void SetMargin(const float m) { SetMargin(m, m, m, m); }
  void SetMargin(const Location l, const float m) {
    if (l != Location::Center) {
      margin_[l] = m;
      Redraw();
    }
  }
  void SetMargin(const float t, const float b, const float l, const float r) {
    margin_[Location::Top] = t;
    margin_[Location::Bottom] = b;
    margin_[Location::Left] = l;
    margin_[Location::Right] = r;
    Redraw();
  }
  void ClearMargin() {
    margin_.clear();
    Redraw();
  }
  void SetBorder(const float b, const SDL_Color c) { SetBorder(b, b, b, b, c); }
  void SetBorder(const Location l, const float b, const SDL_Color c) {
    if (l != Location::Center) {
      border_[l] = std::make_pair(b, c);
      Redraw();
    }
  }
  void SetBorder(const float t, const float b, const float l, const float r,
                 const SDL_Color c) {
    border_[Location::Top] = std::make_pair(t, c);
    border_[Location::Bottom] = std::make_pair(b, c);
    border_[Location::Left] = std::make_pair(l, c);
    border_[Location::Right] = std::make_pair(r, c);
    Redraw();
  }
  void ClearBorder() {
    border_.clear();
    Redraw();
  }
  void SetPadding(const float p) { SetPadding(p, p, p, p); }
  void SetPadding(const Location l, const float p) {
    if (l != Location::Center) {
      padding_[l] = p;
      Redraw();
    }
  }
  void SetPadding(const float t, const float b, const float l, const float r) {
    padding_[Location::Top] = t;
    padding_[Location::Bottom] = b;
    padding_[Location::Left] = l;
    padding_[Location::Right] = r;
    Redraw();
  }
  void ClearPadding() {
    padding_.clear();
    Redraw();
  }
  void SetView(View* v) {
    child_ = v;
    if (v != nullptr) {
      v->SetParent(this);
      v->SetWindow(window_);
    }
    Redraw();
  }
  void ClearView() {
    if (const auto v{child_}; v != nullptr) {
      v->SetParent(nullptr);
      v->SetWindow(nullptr);
    }
    child_ = nullptr;
    Redraw();
  }
  void SetCondition(const Condition condition) override {
    if (const auto v{child_}; v != nullptr) {
      v->SetCondition(condition);
    }
    View::SetCondition(condition);
  }
  void SetSignificance(const Significance significance) override {
    if (const auto v{child_}; v != nullptr) {
      v->SetSignificance(significance);
    }
    View::SetSignificance(significance);
  }
  void SetHorizontalAlignment(const Alignment alignment) override {
    if (const auto v{child_}; v != nullptr) {
      v->SetHorizontalAlignment(alignment);
    }
    View::SetHorizontalAlignment(alignment);
  }
  void SetVerticalAlignment(const Alignment alignment) override {
    if (const auto v{child_}; v != nullptr) {
      v->SetVerticalAlignment(alignment);
    }
    View::SetVerticalAlignment(alignment);
  }
  void SetWindow(Window* window) override {
    if (const auto v{child_}; v != nullptr) {
      v->SetWindow(window);
    }

    View::SetWindow(window);
  }

 private:
  View* child_{nullptr};
  std::map<const Location, float> margin_;
  std::map<const Location, std::pair<float, SDL_Color>> border_;
  std::map<const Location, float> padding_;
};

constexpr float FocusFrameBorderThickness{2};
constexpr float FocusFrameMarginThickness{2};
constexpr float FocusFramePaddingThickness{2};

class FocusFrame : public Frame {
 public:
  FocusFrame() : Frame() {
    SetMargin(FocusFrameMarginThickness + FocusFrameBorderThickness +
              FocusFramePaddingThickness);
  }
  explicit FocusFrame(View* v) : FocusFrame() { SetView(v); }

  FocusFrame(const FocusFrame&) = delete;
  FocusFrame& operator=(const FocusFrame&) = delete;
  FocusFrame(FocusFrame&&) = delete;
  FocusFrame& operator=(FocusFrame&&) = delete;

  void SetCondition(const Condition condition) override {
    View::SetCondition(condition);
    if (IsBitSet(condition_, Condition::Focused)) {
      if (IsBitSet(condition_, Condition::Activated)) {
        SetMargin(FocusFrameMarginThickness + FocusFramePaddingThickness);
        SetBorder(FocusFrameBorderThickness, GetColor(Layer::Foreground));
        ClearPadding();
      } else {
        SetMargin(FocusFrameMarginThickness);
        SetBorder(FocusFrameBorderThickness, GetColor(Layer::Foreground));
        SetPadding(FocusFramePaddingThickness);
      }
    } else {
      SetMargin(FocusFrameMarginThickness + FocusFrameBorderThickness +
                FocusFramePaddingThickness);
      ClearBorder();
      ClearPadding();
    }
  }
};
};  // namespace Pano

#endif  // INCLUDE_PANO_FRAME_H_
