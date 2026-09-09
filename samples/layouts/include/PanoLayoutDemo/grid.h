// Copyright 2026 Stuart Scott
#ifndef SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_GRID_H_
#define SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_GRID_H_
#include <Pano/grid.h>
#include <Pano/text.h>
#include <PanoLayoutDemo/palette.h>

class GridDemo : public Pano::GridLayout {
 public:
  GridDemo();
  ~GridDemo() {
    for (auto v : *this) {
      delete v;
    }
  }
};

#endif  // SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_GRID_H_
