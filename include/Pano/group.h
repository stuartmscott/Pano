// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_GROUP_H_
#define INCLUDE_PANO_GROUP_H_

#include <Pano/constants.h>
#include <Pano/geometry.h>
#include <Pano/view.h>
#include <SDL3/SDL.h>

#include <map>
#include <utility>
#include <vector>

namespace Pano {
class Group : public View {
 public:
  Group(const Group&) = delete;
  Group& operator=(const Group&) = delete;
  Group(Group&&) = delete;
  Group& operator=(Group&&) = delete;

  // Get State
  size_t GetViewCount() const { return views_.size(); }
  class GroupArtist : public Artist {
   public:
    explicit GroupArtist(Group* view) : Artist(view) {}

    void Draw(SDL_Renderer*) override;
  };
  Artist* GetArtist() override {
    if (artist_ == nullptr) {
      artist_ = new GroupArtist(this);
    }
    return View::GetArtist();
  }
  std::vector<View*> GetKeyboardableViews() override;
  std::vector<View*> GetMouseableViews(Point p) override;

  // Set State
  void SetWindow(Window* window) override;
  virtual void AddView(View* view) {
    views_.push_back(view);
    view->SetParent(this);
    view->SetWindow(window_);
    Redraw();
  }
  virtual void ClearViews() {
    for (const auto v : views_) {
      v->SetParent(nullptr);
      v->SetWindow(nullptr);
    }
    views_.clear();
    Redraw();
  }

  // Iteration
  using iterator = std::vector<View*>::iterator;
  using const_iterator = std::vector<View*>::const_iterator;

  iterator begin() { return views_.begin(); }
  iterator end() { return views_.end(); }
  const_iterator cbegin() const { return views_.cbegin(); }
  const_iterator cend() const { return views_.cend(); }

 protected:
  Group() : View() {}
  std::vector<View*> views_;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_GROUP_H_
