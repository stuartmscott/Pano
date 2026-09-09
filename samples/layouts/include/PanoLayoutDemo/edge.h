// Copyright 2026 Stuart Scott
#ifndef SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_EDGE_H_
#define SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_EDGE_H_

#include <Pano/edge.h>
#include <Pano/text.h>

class EdgeDemo : public Pano::EdgeLayout {
 public:
  EdgeDemo();

  Pano::TextView top_{"Top"};
  Pano::TextView bottom_{"Bottom"};
  Pano::TextView left_{"Left"};
  Pano::TextView right_{"Right"};
  Pano::TextView center_{"Center"};
};

#endif  // SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_EDGE_H_
