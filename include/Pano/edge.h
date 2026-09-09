// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_EDGE_H_
#define INCLUDE_PANO_EDGE_H_

#include <Pano/geometry.h>
#include <Pano/group.h>
#include <Pano/view.h>

#include <map>

namespace Pano {
/* EdgeLayout provides a layout structure which can have a view along each
 * edge, and one in the center.*/
class EdgeLayout : public Group {
 public:
  EdgeLayout() : Group() {}

  EdgeLayout(const EdgeLayout&) = delete;
  EdgeLayout& operator=(const EdgeLayout&) = delete;
  EdgeLayout(EdgeLayout&&) = delete;
  EdgeLayout& operator=(EdgeLayout&&) = delete;

  // Get State
  Size GetMinimumSize() const override;

  // Set State
  void SetSize(const Size s) override;
  void SetView(const Location location, View* view) {
    locations_[location] = view;
    Group::AddView(view);
  }
  void ClearViews() override {
    locations_.clear();
    Group::ClearViews();
  }

  static Size Measure(const std::map<const Location, const View*>& locations);

  static void Apply(const Size size, const Point position,
                    const std::map<const Location, View*>& locations);

 protected:
  std::map<const Location, View*> locations_;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_EDGE_H_
