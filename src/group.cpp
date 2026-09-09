// Copyright 2026 Stuart Scott
#include <Pano/group.h>
#include <Pano/log.h>
#include <SDL3/SDL.h>

#include <iostream>
#include <utility>
#include <vector>

namespace Pano {

std::vector<View*> Group::GetKeyboardableViews() {
  std::vector<View*> vs{View::GetKeyboardableViews()};

  for (const auto& v : views_) {
    const auto cs{v->GetKeyboardableViews()};
    vs.insert(vs.end(), cs.begin(), cs.end());
  }

  return vs;
}

std::vector<View*> Group::GetMouseableViews(Point p) {
  std::vector<View*> vs{View::GetMouseableViews(p)};
  if (vs.empty()) {
    // p doesn't intersect this layout
    return vs;
  }

  for (const auto& v : views_) {
    const auto pos{v->GetPosition()};
    const auto cs{v->GetMouseableViews({p.x - pos.x, p.y - pos.y})};
    vs.insert(vs.end(), cs.begin(), cs.end());
  }

  return vs;
}

void Group::SetWindow(Window* window) {
  for (const auto& v : views_) {
    v->SetWindow(window);
  }

  View::SetWindow(window);
}

void Group::GroupArtist::Draw(SDL_Renderer* renderer) {
  View::Artist::Draw(renderer);

  if (texture_ == nullptr) {
    return;
  }

  const auto group{static_cast<Group*>(view_)};
  for (const auto& v : group->views_) {
    DrawView(renderer, texture_, v);
  }
}
};  // namespace Pano
