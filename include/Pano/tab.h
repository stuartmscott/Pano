// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_TAB_H_
#define INCLUDE_PANO_TAB_H_

#include <Pano/button.h>
#include <Pano/constants.h>
#include <Pano/edge.h>
#include <Pano/geometry.h>
#include <Pano/stack.h>
#include <Pano/text.h>
#include <Pano/view.h>
#include <SDL3/SDL.h>

#include <string>
#include <vector>

namespace Pano {
constexpr float TabLayoutIndicatorBorderThickness{2};

/*
Tabs for holding application subsections are typically;
 - static
Tabs for holding documents;
 - dynamic
 - action attached
  - close button
  - dropdown menu
 - scrollable
 - creatable
 - reorderable
 - renameable
 - overflowed into dropdown
*/

class TabLayout : public View {
 public:
  TabLayout() : View() { setup(); }
  ~TabLayout() { teardown(); }

  TabLayout(const TabLayout&) = delete;
  TabLayout& operator=(const TabLayout&) = delete;
  TabLayout(TabLayout&&) = delete;
  TabLayout& operator=(TabLayout&&) = delete;

  // Get State
  Size GetMinimumSize() const override;
  uint32_t GetSelectedTab() const { return selected_tab_; }
  View* GetSelectedContent() const { return tab_contents_[selected_tab_]; }
  class TabLayoutArtist : public Artist {
   public:
    explicit TabLayoutArtist(TabLayout* view) : Artist(view) {}

    void Draw(SDL_Renderer*) override;
  };
  Artist* GetArtist() override {
    if (artist_ == nullptr) {
      artist_ = new TabLayoutArtist(this);
    }
    return View::GetArtist();
  }
  std::vector<View*> GetKeyboardableViews() override;
  std::vector<View*> GetMouseableViews(Point p) override;

  // Set State
  void SetCondition(Condition condition) override {
    for (auto& f : tab_frames_) {
      f->SetCondition(condition);
    }
    View::SetCondition(condition);
  }
  void SetSignificance(Significance significance) override {
    for (auto& f : tab_frames_) {
      f->SetSignificance(significance);
    }
    View::SetSignificance(significance);
  }
  void SetSize(const Size size) override;
  void SetSelectedTab(const uint32_t index);
  void SetHorizontalAlignment(const Alignment alignment) override {
    for (auto& f : tab_frames_) {
      f->SetHorizontalAlignment(alignment);
    }
    View::SetHorizontalAlignment(alignment);
  }
  void SetVerticalAlignment(const Alignment alignment) override {
    for (auto& f : tab_frames_) {
      f->SetVerticalAlignment(alignment);
    }
    View::SetVerticalAlignment(alignment);
  }
  void SetTextAlignment(const TextAlignment alignment) {
    for (auto& b : tab_buttons_) {
      b->SetTextAlignment(alignment);
    }
    Redraw();
  }
  void SetTextTruncation(const TextTruncation truncation) {
    for (auto& b : tab_buttons_) {
      b->SetTextTruncation(truncation);
    }
    Redraw();
  }
  void SetTextWrap(const TextWrap wrap) {
    for (auto& b : tab_buttons_) {
      b->SetTextWrap(wrap);
    }
    Redraw();
  }
  void SetTextStyle(const TextStyle style) {
    for (auto& b : tab_buttons_) {
      b->SetTextStyle(style);
    }
    Redraw();
  }
  void SetTextSize(const int size) {
    for (auto& b : tab_buttons_) {
      b->SetTextSize(size);
    }
    Redraw();
  }
  void SetTabLocation(const Location location);
  void SetWindow(Window* window) override {
    bar_layout_.SetWindow(window);
    content_layout_.SetWindow(window);
    View::SetWindow(window);
  }

  uint32_t AddTab(const std::string name, View* content);

  uint32_t AddTab(const Icon icon, View* content);

  uint32_t AddTab(const std::string name, const Icon icon, View* content);

  void RemoveTab(const uint32_t index);

  void ClearTabs();

  std::function<void(uint32_t)> OnTabSelected{nullptr};

 private:
  void setup();
  void teardown();
  void frame();
  void layout(Size size, Point position);
  uint32_t add_tab(Button* button, View* content);

  uint32_t selected_tab_{0};
  StackLayout bar_layout_{Axis::X};
  StackLayout content_layout_{Axis::Z};
  Axis bar_axis_{Axis::X};
  Location bar_location_{Location::Top};
  std::vector<Frame*> tab_frames_;
  std::vector<Button*> tab_buttons_;
  std::vector<View*> tab_contents_;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_TAB_H_
