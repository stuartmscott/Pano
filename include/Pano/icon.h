// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_ICON_H_
#define INCLUDE_PANO_ICON_H_

#include <Pano/constants.h>
#include <Pano/view.h>
#include <SDL3/SDL.h>

#include <map>

namespace Pano {
constexpr float IconSize{24};

class IconProvider {
 public:
  IconProvider() {}
  virtual ~IconProvider();

  IconProvider(const IconProvider&) = delete;
  IconProvider& operator=(const IconProvider&) = delete;
  IconProvider(IconProvider&&) = delete;
  IconProvider& operator=(IconProvider&&) = delete;

  virtual SDL_Texture* GetIcon(SDL_Renderer* renderer, Icon icon);
  void SetIcon(Icon icon, SDL_Texture* texture) { icons_[icon] = texture; }

 protected:
  SDL_Texture* load_icon(SDL_Renderer* renderer, Icon icon, const void* data,
                         const size_t size);
  std::map<Icon, SDL_Texture*> icons_;
};

class IconView : public View {
 public:
  IconView() : View() {}
  explicit IconView(Icon icon) : View() { SetIcon(icon); }
  ~IconView() {}

  IconView(const IconView&) = delete;
  IconView& operator=(const IconView&) = delete;
  IconView(IconView&&) = delete;
  IconView& operator=(IconView&&) = delete;

  // Get State
  Size GetMinimumSize() const override {
    if (icon_ == Icon::None) {
      return {0, 0};
    }
    return {IconSize, IconSize};
  }
  class IconViewArtist : public Artist {
   public:
    explicit IconViewArtist(IconView* view) : Artist(view) {}

    void Draw(SDL_Renderer*) override;
  };

  Artist* GetArtist() override {
    if (artist_ == nullptr) {
      artist_ = new IconViewArtist(this);
    }
    return View::GetArtist();
  }
  Icon GetIcon() { return icon_; }

  // Set State
  void SetIcon(Icon icon) {
    icon_ = icon;
    Redraw();
  }
  void ClearIcon() { SetIcon(Icon::None); }

 protected:
  Icon icon_{Icon::None};
};
};  // namespace Pano

#endif  // INCLUDE_PANO_ICON_H_
