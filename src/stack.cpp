// Copyright 2026 Stuart Scott
#include <Pano/stack.h>

#include <vector>

namespace Pano {

Size StackLayout::GetMinimumSize() const {
  std::vector<const View*> views(views_.begin(), views_.end());
  return StackLayout::Measure(axis_, views);
}

void StackLayout::SetSize(Size s) {
  StackLayout::Apply(s, position_, axis_, views_);
  View::SetSize(s);
}

Size StackLayout::Measure(const Axis axis,
                          const std::vector<const View*>& views) {
  float width{0};
  float height{0};

  for (const auto v : views) {
    const auto s{v->GetMinimumSize()};

    switch (axis) {
      case Axis::X: {
        width += s.width;

        if (s.height > height) {
          height = s.height;
        }
        break;
      }
      case Axis::Y: {
        if (s.width > width) {
          width = s.width;
        }

        height += s.height;
        break;
      }
      case Axis::Z: {
        if (s.width > width) {
          width = s.width;
        }

        if (s.height > height) {
          height = s.height;
        }
        break;
      }
    }
  }
  return {width, height};
}

void StackLayout::Apply(const Size size, const Point position, const Axis axis,
                        const std::vector<View*>& views) {
  float x{0};
  float y{0};
  float z{position.z + 1};

  const auto count{views.size()};
  float part_width{size.width / count};
  float part_height{size.height / count};

  for (auto& v : views) {
    switch (axis) {
      case Axis::X: {
        v->SetPosition({x, y, z});
        v->SetSize({part_width, size.height});
        x += part_width;
        break;
      }
      case Axis::Y: {
        v->SetPosition({x, y, z});
        v->SetSize({size.width, part_height});
        y += part_height;
        break;
      }
      case Axis::Z: {
        v->SetPosition({x, y, z});
        v->SetSize(size);
        z++;
        break;
      }
    }
  }
}
};  // namespace Pano
