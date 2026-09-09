// Copyright 2026 Stuart Scott
#ifndef SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_TAB_H_
#define SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_TAB_H_
#include <Pano/app.h>
#include <Pano/constants.h>
#include <Pano/edge.h>
#include <Pano/frame.h>
#include <Pano/grid.h>
#include <Pano/radio.h>
#include <Pano/tab.h>
#include <Pano/text.h>
#include <PanoLayoutDemo/palette.h>

#include <map>
#include <string>

const std::map<const std::string, const Pano::Location> Locations{
    {"Top", Pano::Location::Top},
    {"Bottom", Pano::Location::Bottom},
    {"Left", Pano::Location::Left},
    {"Right", Pano::Location::Right}};

class TabDemo : public Pano::EdgeLayout {
 public:
  TabDemo();

  Pano::TextView text1_{"1"};
  Pano::TextView text2_{"2"};
  Pano::TextView text3_{"3"};
  Pano::TextView text4_{"4"};
  Pano::TabLayout tabs_;
  Pano::Frame frame_;
  Pano::RadioGroup radio_{{"Top", "Bottom", "Left", "Right"}};
  Pano::TextView radio_label_{"Tab Location"};
  Pano::GridLayout grid_{1, 5};
};

#endif  // SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_TAB_H_
