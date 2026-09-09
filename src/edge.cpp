// Copyright 2026 Stuart Scott
#include <Pano/edge.h>
#include <Pano/log.h>

#include <map>

namespace Pano {

Size EdgeLayout::GetMinimumSize() const {
  std::map<const Location, const View*> locations(locations_.begin(),
                                                  locations_.end());
  return EdgeLayout::Measure(locations);
}

void EdgeLayout::SetSize(Size s) {
  EdgeLayout::Apply(s, position_, locations_);

  View::SetSize(s);
}

Size EdgeLayout::Measure(
    const std::map<const Location, const View*>& locations) {
  float width{0};
  float height{0};

  if (const auto it{locations.find(Location::Center)}; it != locations.end()) {
    const auto s{it->second->GetMinimumSize()};
    width += s.width;
    height += s.height;
  }

  if (const auto it{locations.find(Location::Top)}; it != locations.end()) {
    const auto s{it->second->GetMinimumSize()};
    height += s.height;
  }

  if (const auto it{locations.find(Location::Bottom)}; it != locations.end()) {
    const auto s{it->second->GetMinimumSize()};
    height += s.height;
  }

  if (const auto it{locations.find(Location::Left)}; it != locations.end()) {
    const auto s{it->second->GetMinimumSize()};
    width += s.width;
  }

  if (const auto it{locations.find(Location::Right)}; it != locations.end()) {
    const auto s{it->second->GetMinimumSize()};
    width += s.width;
  }

  return {width, height};
}

void EdgeLayout::Apply(const Size size, const Point position,
                       const std::map<const Location, View*>& locations) {
  const auto z{position.z + 1};

  Size top{};
  Size bottom{};
  Size left{};
  Size right{};

  if (const auto it{locations.find(Location::Top)}; it != locations.end()) {
    top = it->second->GetMinimumSize();
    it->second->SetPosition({0, 0, z});
    it->second->SetSize({size.width, top.height});
  }

  if (const auto it{locations.find(Location::Bottom)}; it != locations.end()) {
    bottom = it->second->GetMinimumSize();
    it->second->SetPosition({0, size.height - bottom.height, z});
    it->second->SetSize({size.width, bottom.height});
  }

  if (const auto it{locations.find(Location::Left)}; it != locations.end()) {
    left = it->second->GetMinimumSize();
    it->second->SetPosition({0, top.height, z});
    it->second->SetSize({left.width, size.height - top.height - bottom.height});
  }

  if (const auto it{locations.find(Location::Right)}; it != locations.end()) {
    right = it->second->GetMinimumSize();
    it->second->SetPosition({size.width - right.width, top.height, z});
    it->second->SetSize(
        {right.width, size.height - top.height - bottom.height});
  }

  if (const auto it{locations.find(Location::Center)}; it != locations.end()) {
    it->second->SetPosition({left.width, top.height, z});
    it->second->SetSize({size.width - left.width - right.width,
                         size.height - top.height - bottom.height});
  }
}
};  // namespace Pano
