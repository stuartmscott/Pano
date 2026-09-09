// Copyright 2026 Stuart Scott
#ifndef SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_STACK_H_
#define SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_STACK_H_
#include <Pano/app.h>
#include <Pano/constants.h>
#include <Pano/edge.h>
#include <Pano/frame.h>
#include <Pano/grid.h>
#include <Pano/radio.h>
#include <Pano/stack.h>
#include <Pano/text.h>
#include <PanoLayoutDemo/palette.h>

#include <map>
#include <string>

const std::map<const std::string, const Pano::Axis> Axes{
    {"X", Pano::Axis::X}, {"Y", Pano::Axis::Y}, {"Z", Pano::Axis::Z}};

class StackDemo : public Pano::EdgeLayout {
 public:
  StackDemo();

  Pano::TextView text1_{"1"};
  Pano::TextView text2_{"2"};
  Pano::TextView text3_{"3"};
  Pano::TextView text4_{"4"};
  Pano::StackLayout stack_;
  Pano::Frame frame_;
  Pano::RadioGroup radio_{{"X", "Y", "Z"}};
  Pano::TextView radio_label_{"Axis"};
  Pano::GridLayout grid_{1, 4};
};

#endif  // SAMPLES_LAYOUTS_INCLUDE_PANOLAYOUTDEMO_STACK_H_
