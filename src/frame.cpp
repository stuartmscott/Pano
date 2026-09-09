// Copyright 2026 Stuart Scott
#include <Pano/frame.h>
#include <Pano/log.h>
#include <SDL3/SDL.h>

#include <iostream>
#include <vector>

namespace Pano {

std::vector<View*> Frame::GetKeyboardableViews() {
  std::vector<View*> vs{View::GetKeyboardableViews()};

  if (const auto v{child_}; v != nullptr) {
    const auto cs{v->GetKeyboardableViews()};
    vs.insert(vs.end(), cs.begin(), cs.end());
  }

  return vs;
}

std::vector<View*> Frame::GetMouseableViews(Point p) {
  std::vector<View*> vs{View::GetMouseableViews(p)};
  if (vs.empty()) {
    // p doesn't intersect this layout
    return vs;
  }

  if (const auto v{child_}; v != nullptr) {
    const auto pos{v->GetPosition()};
    const auto cs{v->GetMouseableViews({p.x - pos.x, p.y - pos.y})};
    vs.insert(vs.end(), cs.begin(), cs.end());
  }

  return vs;
}

Size Frame::GetMinimumSize() const {
  float width{0};
  float height{0};

  // Margin
  if (const auto it{margin_.find(Location::Top)}; it != margin_.end()) {
    height += it->second;
  }
  if (const auto it{margin_.find(Location::Bottom)}; it != margin_.end()) {
    height += it->second;
  }
  if (const auto it{margin_.find(Location::Left)}; it != margin_.end()) {
    width += it->second;
  }
  if (const auto it{margin_.find(Location::Right)}; it != margin_.end()) {
    width += it->second;
  }

  // Border
  if (const auto it{border_.find(Location::Top)}; it != border_.end()) {
    height += it->second.first;
  }
  if (const auto it{border_.find(Location::Bottom)}; it != border_.end()) {
    height += it->second.first;
  }
  if (const auto it{border_.find(Location::Left)}; it != border_.end()) {
    width += it->second.first;
  }
  if (const auto it{border_.find(Location::Right)}; it != border_.end()) {
    width += it->second.first;
  }

  // Padding
  if (const auto it{padding_.find(Location::Top)}; it != padding_.end()) {
    height += it->second;
  }
  if (const auto it{padding_.find(Location::Bottom)}; it != padding_.end()) {
    height += it->second;
  }
  if (const auto it{padding_.find(Location::Left)}; it != padding_.end()) {
    width += it->second;
  }
  if (const auto it{padding_.find(Location::Right)}; it != padding_.end()) {
    width += it->second;
  }

  // Content
  if (child_ != nullptr) {
    const auto s{child_->GetMinimumSize()};
    width += s.width;
    height += s.height;
  }

  return {width, height};
}

void Frame::SetSize(Size s) {
  float x{0};
  float y{0};
  float z{position_.z + 1};
  float width{s.width};
  float height{s.height};

  // Margin
  if (const auto it{margin_.find(Location::Top)}; it != margin_.end()) {
    y += it->second;
    height -= it->second;
  }
  if (const auto it{margin_.find(Location::Bottom)}; it != margin_.end()) {
    height -= it->second;
  }
  if (const auto it{margin_.find(Location::Left)}; it != margin_.end()) {
    x += it->second;
    width -= it->second;
  }
  if (const auto it{margin_.find(Location::Right)}; it != margin_.end()) {
    width -= it->second;
  }

  // Border
  if (const auto it{border_.find(Location::Top)}; it != border_.end()) {
    y += it->second.first;
    height -= it->second.first;
  }
  if (const auto it{border_.find(Location::Bottom)}; it != border_.end()) {
    height -= it->second.first;
  }
  if (const auto it{border_.find(Location::Left)}; it != border_.end()) {
    x += it->second.first;
    width -= it->second.first;
  }
  if (const auto it{border_.find(Location::Right)}; it != border_.end()) {
    width -= it->second.first;
  }

  // Padding
  if (const auto it{padding_.find(Location::Top)}; it != padding_.end()) {
    y += it->second;
    height -= it->second;
  }
  if (const auto it{padding_.find(Location::Bottom)}; it != padding_.end()) {
    height -= it->second;
  }
  if (const auto it{padding_.find(Location::Left)}; it != padding_.end()) {
    x += it->second;
    width -= it->second;
  }
  if (const auto it{padding_.find(Location::Right)}; it != padding_.end()) {
    width -= it->second;
  }

  // Content
  if (child_ != nullptr) {
    child_->SetPosition({x, y, z});
    child_->SetSize({width, height});
  }

  View::SetSize(s);
}

void Frame::FrameArtist::Draw(SDL_Renderer* renderer) {
  View::Artist::Draw(renderer);

  if (texture_ == nullptr) {
    return;
  }

  const auto frame{static_cast<Frame*>(view_)};
  const auto child{frame->child_};

  // View
  if (child != nullptr && child->IsVisible()) {
    const auto position{child->GetPosition()};
    const auto size{child->GetSize()};
    const auto artist{child->GetArtist()};
    if (artist != nullptr) {
      if (child->IsDirty()) {
        artist->BeforeDraw(renderer);
        artist->Draw(renderer);
        artist->AfterDraw(renderer);
      }

      const auto texture{artist->GetTexture()};
      if (texture != nullptr) {
        if (!SDL_SetRenderTarget(renderer, texture_)) {
          Error() << "Failed to set render target: " << SDL_GetError()
                  << std::endl;
        }

        if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
          Error() << "Failed to set blend mode: " << SDL_GetError()
                  << std::endl;
        }

        SDL_FRect src{0, 0, static_cast<float>(size.width),
                      static_cast<float>(size.height)};
        SDL_FRect dest{static_cast<float>(position.x),
                       static_cast<float>(position.y), src.w, src.h};

        if (!SDL_RenderTexture(renderer, texture, &src, &dest)) {
          Error() << "Failed to render texture: " << SDL_GetError()
                  << std::endl;
        }
      }
    }
  }

  // Border
  const auto margin{frame->margin_};
  float margin_top{0};
  float margin_bottom{0};
  float margin_left{0};
  float margin_right{0};
  if (const auto it{margin.find(Location::Top)}; it != margin.end()) {
    margin_top = it->second;
  }
  if (const auto it{margin.find(Location::Bottom)}; it != margin.end()) {
    margin_bottom = it->second;
  }
  if (const auto it{margin.find(Location::Left)}; it != margin.end()) {
    margin_left = it->second;
  }
  if (const auto it{margin.find(Location::Right)}; it != margin.end()) {
    margin_right = it->second;
  }

  const auto size{frame->GetSize()};
  const auto border{frame->border_};
  if (const auto it{border.find(Location::Top)}; it != border.end()) {
    draw_border(renderer, {margin_left, margin_top},
                {size.width - margin_left - margin_right, it->second.first},
                it->second.second);
  }
  if (const auto it{border.find(Location::Bottom)}; it != border.end()) {
    draw_border(renderer,
                {margin_left, size.height - margin_bottom - it->second.first},
                {size.width - margin_left - margin_right, it->second.first},
                it->second.second);
  }
  if (const auto it{border.find(Location::Left)}; it != border.end()) {
    draw_border(renderer, {margin_left, margin_top},
                {it->second.first, size.height - margin_top - margin_bottom},
                it->second.second);
  }
  if (const auto it{border.find(Location::Right)}; it != border.end()) {
    draw_border(renderer,
                {size.width - margin_right - it->second.first, margin_top},
                {it->second.first, size.height - margin_top - margin_bottom},
                it->second.second);
  }
}

void Frame::FrameArtist::draw_border(SDL_Renderer* renderer, Point p, Size s,
                                     SDL_Color c) {
  if (!SDL_SetRenderTarget(renderer, texture_)) {
    Error() << "Failed to set render target: " << SDL_GetError() << std::endl;
  }

  if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
    Error() << "Failed to set blend mode: " << SDL_GetError() << std::endl;
  }

  if (!SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a)) {
    Error() << "Failed to set draw color: " << SDL_GetError() << std::endl;
  }

  SDL_FRect rect{p.x, p.y, s.width, s.height};
  if (!SDL_RenderFillRect(renderer, &rect)) {
    Error() << "Failed to fill rectangle: " << SDL_GetError() << std::endl;
  }
}
};  // namespace Pano
