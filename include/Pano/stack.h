// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_STACK_H_
#define INCLUDE_PANO_STACK_H_

#include <Pano/constants.h>
#include <Pano/geometry.h>
#include <Pano/group.h>
#include <Pano/view.h>

#include <vector>

namespace Pano {
/* StackLayout lays child views out along a single axis;
 * X - left to right
 * Y - top to bottom
 * Z - back to front
 */
class StackLayout : public Group {
 public:
  StackLayout() : StackLayout(Axis::X) {}
  explicit StackLayout(Axis axis) : Group(), axis_(axis) {}

  StackLayout(const StackLayout&) = delete;
  StackLayout& operator=(const StackLayout&) = delete;
  StackLayout(StackLayout&&) = delete;
  StackLayout& operator=(StackLayout&&) = delete;

  // Get State
  Axis GetAxis() const;
  Size GetMinimumSize() const override;

  // Set State
  void SetAxis(const Axis axis) {
    axis_ = axis;
    Apply(size_, position_, axis_, views_);
    Redraw();
  }
  void SetSize(const Size s) override;

  static Size Measure(const Axis axis, const std::vector<const View*>& views);

  static void Apply(const Size size, const Point position, const Axis axis,
                    const std::vector<View*>& views);

 protected:
  Axis axis_;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_STACK_H_
