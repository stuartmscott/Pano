// Copyright 2026 Stuart Scott
#include <Pano/grid.h>

#include <map>
#include <utility>

namespace Pano {

Size GridLayout::GetMinimumSize() const {
  std::map<const std::pair<uint32_t, uint32_t>, const View*> locations{
      locations_.begin(), locations_.end()};
  std::map<const std::pair<uint32_t, uint32_t>,
           const std::pair<uint32_t, uint32_t>>
      spans{spans_.begin(), spans_.end()};
  return GridLayout::Measure(rows_, columns_, locations, spans);
}

void GridLayout::SetSize(Size s) {
  std::map<const std::pair<uint32_t, uint32_t>, View*> locations{
      locations_.begin(), locations_.end()};
  std::map<const std::pair<uint32_t, uint32_t>,
           const std::pair<uint32_t, uint32_t>>
      spans{spans_.begin(), spans_.end()};
  GridLayout::Apply(s, position_, rows_, columns_, locations, spans);
  View::SetSize(s);
}

Size GridLayout::Measure(
    const uint32_t rows, const uint32_t columns,
    const std::map<const std::pair<uint32_t, uint32_t>, const View*>& locations,
    const std::map<const std::pair<uint32_t, uint32_t>,
                   const std::pair<uint32_t, uint32_t>>& spans) {
  float max_width{0};
  float max_height{0};

  for (uint32_t r{0}; r < rows; ++r) {
    for (uint32_t c{0}; c < columns; ++c) {
      const auto key{std::make_pair(r, c)};
      if (const auto lit{locations.find(key)}; lit != locations.end()) {
        const auto s{lit->second->GetMinimumSize()};

        uint32_t row_span{1};
        uint32_t column_span{1};
        if (const auto sit{spans.find(key)}; sit != spans.end()) {
          row_span = sit->second.first;
          column_span = sit->second.second;
        }

        const auto width{s.width / column_span};
        const auto height{s.height / row_span};
        if (width > max_width) {
          max_width = width;
        }

        if (height > max_height) {
          max_height = height;
        }
      }
    }
  }

  return {max_width * columns, max_height * rows};
}

void GridLayout::Apply(
    const Size size, const Point position, const uint32_t rows,
    const uint32_t columns,
    const std::map<const std::pair<uint32_t, uint32_t>, View*>& locations,
    const std::map<const std::pair<uint32_t, uint32_t>,
                   const std::pair<uint32_t, uint32_t>>& spans) {
  const auto z{position.z + 1};

  float width{size.width / columns};
  float height{size.height / rows};

  for (uint32_t r{0}; r < rows; ++r) {
    for (uint32_t c{0}; c < columns; ++c) {
      const auto key{std::make_pair(r, c)};
      if (const auto lit{locations.find(key)}; lit != locations.end()) {
        float x{c * width};
        float y{r * height};
        lit->second->SetPosition({x, y, z});

        uint32_t row_span{1};
        uint32_t column_span{1};
        if (const auto sit{spans.find(key)}; sit != spans.end()) {
          row_span = sit->second.first;
          column_span = sit->second.second;
        }

        lit->second->SetSize({column_span * width, row_span * height});
      }
    }
  }
}
};  // namespace Pano
