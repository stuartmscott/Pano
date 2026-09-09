// Copyright 2026 Stuart Scott
#include <Pano/color.h>
#include <Pano/log.h>
#include <SDL3/SDL.h>

#include <sstream>
#include <string>
#include <utility>

namespace Pano {

SDL_Color ColorProvider::GetColor(Significance significance,
                                  Condition condition, Layer layer) const {
  const auto id{std::make_tuple(significance, condition, layer)};
  if (const auto it{colors_.find(id)}; it != colors_.end()) {
    return it->second;
  }
  Error() << "Failed to find color for: " << ToString(significance) << ' '
          << ToString(condition) << ' ' << ToString(layer) << std::endl;
  return fallback_;
}

void ColorProvider::SetColor(Significance significance, Condition condition,
                             Layer layer, SDL_Color color) {
  const auto id{std::make_tuple(significance, condition, layer)};
  colors_[id] = color;
}
};  // namespace Pano
