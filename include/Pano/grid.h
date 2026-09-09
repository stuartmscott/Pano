// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_GRID_H_
#define INCLUDE_PANO_GRID_H_

#include <Pano/geometry.h>
#include <Pano/group.h>
#include <Pano/view.h>

#include <map>
#include <utility>

namespace Pano {
/* GridLayout provides a grid of rows and columns in which a set of views can be
 * rendered. Views can also be configured to span multiple rows and/or
 * columns.*/
class GridLayout : public Group {
 public:
  GridLayout(uint32_t rows, uint32_t columns)
      : Group(), rows_(rows), columns_(columns) {}

  GridLayout(const GridLayout&) = delete;
  GridLayout& operator=(const GridLayout&) = delete;
  GridLayout(GridLayout&&) = delete;
  GridLayout& operator=(GridLayout&&) = delete;

  // Get State
  Size GetMinimumSize() const override;
  std::pair<uint32_t, uint32_t> GetSpan(uint32_t row, uint32_t column) {
    if (const auto it{spans_.find(std::make_pair(row, column))};
        it != spans_.end()) {
      return it->second;
    }
    return std::make_pair(1, 1);
  }

  // Set State
  void SetSize(const Size s) override;
  void SetSpan(const uint32_t row, const uint32_t column, const uint32_t rows,
               const uint32_t columns) {
    spans_[std::make_pair(row, column)] = std::make_pair(rows, columns);
    Redraw();
  }
  void SetView(const uint32_t row, const uint32_t column, View* view) {
    if (row >= rows_ || column >= columns_) {
      return;
    }
    locations_[std::make_pair(row, column)] = view;
    Group::AddView(view);
  }
  void SetView(const uint32_t row, const uint32_t column, View* view,
               const uint32_t rows, const uint32_t columns) {
    SetView(row, column, view);
    SetSpan(row, column, rows, columns);
  }
  void ClearViews() override {
    locations_.clear();
    Group::ClearViews();
  }

  static Size Measure(
      const uint32_t rows, const uint32_t columns,
      const std::map<const std::pair<uint32_t, uint32_t>, const View*>&
          locations,
      const std::map<const std::pair<uint32_t, uint32_t>,
                     const std::pair<uint32_t, uint32_t>>& spans);

  static void Apply(
      const Size size, const Point position, const uint32_t rows,
      const uint32_t columns,
      const std::map<const std::pair<uint32_t, uint32_t>, View*>& locations,
      const std::map<const std::pair<uint32_t, uint32_t>,
                     const std::pair<uint32_t, uint32_t>>& spans);

 protected:
  uint32_t rows_{0};
  uint32_t columns_{0};
  std::map<std::pair<uint32_t, uint32_t>, View*> locations_;
  std::map<std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>> spans_;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_GRID_H_
