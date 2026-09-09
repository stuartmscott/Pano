// Copyright 2026 Stuart Scott
#include <Pano/constants.h>
#include <Pano/log.h>
#include <Pano/tab.h>
#include <SDL3/SDL.h>

#include <map>
#include <string>
#include <vector>

namespace Pano {

void TabLayout::setup() {
  bar_layout_.SetParent(this);
  content_layout_.SetParent(this);
}

void TabLayout::teardown() { ClearTabs(); }

void TabLayout::frame() {
  float t{0};
  float b{0};
  float l{0};
  float r{0};
  switch (bar_location_) {
    case Location::Top:
      b = TabLayoutIndicatorBorderThickness;
      break;
    case Location::Bottom:
      t = TabLayoutIndicatorBorderThickness;
      break;
    case Location::Left:
      r = TabLayoutIndicatorBorderThickness;
      break;
    case Location::Right:
      l = TabLayoutIndicatorBorderThickness;
      break;
    default:
      break;
  }
  const auto colors{App::current_->GetColorProvider()};
  const auto bg{colors->GetColor(significance_, condition_, Layer::Background)};
  const auto fg{colors->GetColor(significance_, condition_, Layer::Foreground)};
  for (uint32_t i{0}; i < tab_frames_.size(); ++i) {
    if (selected_tab_ == i) {
      tab_frames_[i]->SetBorder(t, b, l, r, fg);
    } else {
      tab_frames_[i]->SetBorder(t, b, l, r, bg);
    }
  }
}

void TabLayout::layout(Size size, Point position) {
  std::map<const Location, View*> locations;
  locations[bar_location_] = &bar_layout_;
  locations[Location::Center] = &content_layout_;
  EdgeLayout::Apply(size, position, locations);
}

Size TabLayout::GetMinimumSize() const {
  std::map<const Location, const View*> locations;
  locations[bar_location_] = &bar_layout_;
  locations[Location::Center] = &content_layout_;
  return EdgeLayout::Measure(locations);
}

std::vector<View*> TabLayout::GetKeyboardableViews() {
  std::vector<View*> vs{View::GetKeyboardableViews()};

  for (auto& f : tab_frames_) {
    const auto cs{f->GetKeyboardableViews()};
    vs.insert(vs.end(), cs.begin(), cs.end());
  }

  if (auto v{GetSelectedContent()}; v != nullptr) {
    const auto cs{v->GetKeyboardableViews()};
    vs.insert(vs.end(), cs.begin(), cs.end());
  }

  return vs;
}

std::vector<View*> TabLayout::GetMouseableViews(Point p) {
  std::vector<View*> vs{View::GetMouseableViews(p)};
  if (vs.empty()) {
    // p doesn't intersect this layout
    return vs;
  }

  const auto bar_position{bar_layout_.GetPosition()};
  for (auto& f : tab_frames_) {
    const auto frame_position{f->GetPosition()};
    const auto cs{
        f->GetMouseableViews({p.x - bar_position.x - frame_position.x,
                              p.y - bar_position.y - frame_position.y})};
    vs.insert(vs.end(), cs.begin(), cs.end());
  }

  if (auto v{GetSelectedContent()}; v != nullptr) {
    const auto layout_position{content_layout_.GetPosition()};
    const auto content_position{v->GetPosition()};
    const auto cs{
        v->GetMouseableViews({p.x - layout_position.x - content_position.x,
                              p.y - layout_position.y - content_position.y})};
    vs.insert(vs.end(), cs.begin(), cs.end());
  }

  return vs;
}

void TabLayout::SetSize(const Size size) {
  layout(size, position_);
  View::SetSize(size);
}

void TabLayout::SetSelectedTab(const uint32_t index) {
  Info() << "SetSelectedTab: " << index << std::endl;
  selected_tab_ = index;
  frame();
  for (uint32_t i{0}; i < tab_contents_.size(); ++i) {
    if (index == i) {
      tab_contents_[i]->SetVisible(true);
    } else {
      tab_contents_[i]->SetVisible(false);
    }
  }
  Redraw();
  if (const auto h{OnTabSelected}; h != nullptr) {
    h(index);
  }
}

void TabLayout::SetTabLocation(const Location location) {
  if (location != Location::Center) {
    bar_location_ = location;
    bar_axis_ = Axis::X;
    if (location == Location::Left || location == Location::Right) {
      bar_axis_ = Axis::Y;
    }
    bar_layout_.SetAxis(bar_axis_);
    frame();
    layout(size_, position_);
    Redraw();
  }
}

void TabLayout::ClearTabs() {
  bar_layout_.ClearViews();
  content_layout_.ClearViews();
  for (const auto b : tab_buttons_) {
    delete b;
  }
  for (const auto f : tab_frames_) {
    delete f;
  }
  tab_buttons_.clear();
  tab_frames_.clear();
  tab_contents_.clear();
}

uint32_t TabLayout::AddTab(const std::string name, View* content) {
  return add_tab(new Button(name), content);
}

uint32_t TabLayout::AddTab(const Icon icon, View* content) {
  return add_tab(new Button(icon), content);
}

uint32_t TabLayout::AddTab(const std::string name, const Icon icon,
                           View* content) {
  return add_tab(new Button(name, icon), content);
}

uint32_t TabLayout::add_tab(Button* button, View* content) {
  const uint32_t index{static_cast<uint32_t>(tab_buttons_.size())};
  button->OnPressed = [&, index]() { SetSelectedTab(index); };
  button->SetIconLocation(Location::Top);
  button->SetSignificance(Significance::Normal);
  button->SetTextAlignment(TextAlignment::Center);
  button->SetVerticalAlignment(Alignment::Center);
  auto frame = new Frame(button);
  bar_layout_.AddView(frame);
  content_layout_.AddView(content);
  tab_frames_.push_back(frame);
  tab_buttons_.push_back(button);
  tab_contents_.push_back(content);
  if (index == 0) {
    SetSize(size_);  // Force re-layout
    SetSelectedTab(index);
  } else {
    content->SetVisible(false);
    Redraw();
  }
  return index;
}

void TabLayout::TabLayoutArtist::Draw(SDL_Renderer* renderer) {
  View::Artist::Draw(renderer);

  if (texture_ == nullptr) {
    return;
  }

  const auto tl{static_cast<TabLayout*>(view_)};
  DrawView(renderer, texture_, &(tl->bar_layout_));
  DrawView(renderer, texture_, &(tl->content_layout_));
}
};  // namespace Pano
