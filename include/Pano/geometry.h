// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_GEOMETRY_H_
#define INCLUDE_PANO_GEOMETRY_H_

namespace Pano {
struct Point {
  float x{0};
  float y{0};
  float z{0};
};

struct Size {
  float width{0};
  float height{0};
  float depth{0};
};
};  // namespace Pano

#endif  // INCLUDE_PANO_GEOMETRY_H_
