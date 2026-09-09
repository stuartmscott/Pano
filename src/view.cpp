// Copyright 2026 Stuart Scott
#include <Pano/app.h>
#include <Pano/log.h>
#include <Pano/view.h>
#include <SDL3/SDL.h>

#include <algorithm>
#include <bit>
#include <cmath>
#include <vector>

namespace Pano {

View::~View() {
  if (artist_ != nullptr) {
    delete artist_;
    artist_ = nullptr;
  }
}

SDL_Color View::GetColor(Layer layer) const {
  if (layer == Layer::Background && background_color_overriden_) {
    return background_color_;
  }
  if (layer == Layer::Foreground && foreground_color_overriden_) {
    return foreground_color_;
  }

  const auto colors{App::current_->GetColorProvider()};
  if (IsEnabled()) {
    return colors->GetColor(significance_, condition_, layer);
  }
  return colors->GetColor(significance_, Condition::Disabled, layer);
}

std::vector<View*> View::GetKeyboardableViews() {
  std::vector<View*> vs;
  if (visible_ && OnKeyboardFocusGained != nullptr) {
    vs.push_back(this);
  }
  return vs;
}

std::vector<View*> View::GetMouseableViews(Point p) {
  std::vector<View*> vs;
  if (visible_ && p.x >= 0 && p.y >= 0 && p.x < size_.width &&
      p.y < size_.height) {
    vs.push_back(this);
  }
  return vs;
}
/*
// Split into;
// - Focus - for input & tabbing
// - Hover - for touch & mouse events

void View::HandleKeyboard(SDL_KeyboardEvent& e) {
  // Forward to view currently holding focus (if any)
}

void View::HandlePointer(SDL_TouchFingerEvent& e) {
  // Forward to view under pointer position
}

void View::HandleMouseButton(SDL_MouseButtonEvent& e) {
  // Forward to view under mouse position
}

void View::HandleMouseMotion(SDL_MouseMotionEvent& e) {
  // Forward to view under mouse position
  // TODO generate hover events
}

void View::HandleMouseWheel(SDL_MouseWheelEvent& e) {
  // Forward to view under mouse position
}
*/

std::vector<View*> GetSortedMouseableViews(View* v, Point p) {
  std::vector<View*> vs{v->GetMouseableViews(p)};
  // sort by z descending
  std::sort(vs.begin(), vs.end(), [](const View* a, const View* b) {
    return a->GetPosition().z > b->GetPosition().z;
  });
  return vs;
}

View::Artist::~Artist() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
}

void View::Artist::BeforeDraw(SDL_Renderer* renderer) {
  const auto size{view_->GetSize()};
  if (texture_ != nullptr && (texture_size_.width < size.width ||
                              texture_size_.height < size.height)) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }

  if (texture_ == nullptr && size.width > 0 && size.height > 0) {
    view_->dirty_ = true;
    texture_size_.width =
        std::bit_ceil(static_cast<uint32_t>(std::ceil(size.width)));
    texture_size_.height =
        std::bit_ceil(static_cast<uint32_t>(std::ceil(size.height)));
    texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET, texture_size_.width,
                                 texture_size_.height);
    if (texture_ == nullptr) {
      Error() << "Failed to create texture: " << texture_size_.width << 'x'
              << texture_size_.height << ": " << SDL_GetError() << std::endl;
    }
  }
}

void View::Artist::Draw(SDL_Renderer* renderer) {
  if (texture_ == nullptr) {
    return;
  }

  if (!SDL_SetRenderTarget(renderer, texture_)) {
    Error() << "Failed to set render target: " << SDL_GetError() << std::endl;
  }

  const auto bg{view_->GetColor(Layer::Background)};
  if (!SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a)) {
    Error() << "Failed to set draw color: " << SDL_GetError() << std::endl;
  }
  if (!SDL_RenderClear(renderer)) {
    Error() << "Failed to clear: " << SDL_GetError() << std::endl;
  }
}

void View::Artist::AfterDraw(SDL_Renderer* renderer) {
  if (texture_ == nullptr) {
    return;
  }
  view_->dirty_ = false;
}

void DrawView(SDL_Renderer* renderer, SDL_Texture* texture, View* view) {
  if (view == nullptr || !view->IsVisible()) {
    return;
  }
  const auto a{view->GetArtist()};
  if (a == nullptr) {
    return;
  }

  if (view->IsDirty()) {
    if (a != nullptr) {
      a->BeforeDraw(renderer);
      a->Draw(renderer);
      a->AfterDraw(renderer);
    }
  }

  const auto tex{a->GetTexture()};
  if (tex == nullptr) {
    return;
  }

  if (!SDL_SetRenderTarget(renderer, texture)) {
    Error() << "Failed to set render target: " << SDL_GetError() << std::endl;
  }

  if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
    Error() << "Failed to set blend mode: " << SDL_GetError() << std::endl;
  }

  const auto position{view->GetPosition()};
  const auto size{view->GetSize()};

  SDL_FRect src{0, 0, static_cast<float>(size.width),
                static_cast<float>(size.height)};
  SDL_FRect dest{static_cast<float>(position.x), static_cast<float>(position.y),
                 src.w, src.h};

  if (!SDL_RenderTexture(renderer, tex, &src, &dest)) {
    Error() << "Failed to render texture: " << SDL_GetError() << std::endl;
  }
}
};  // namespace Pano
