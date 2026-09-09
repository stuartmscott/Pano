// Copyright 2026 Stuart Scott
#ifndef SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_BUTTON_H_
#define SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_BUTTON_H_

#include <Pano/button.h>
#include <Pano/grid.h>
#include <Pano/utf.h>

#include <string>

class ButtonDemo : public Pano::GridLayout {
 public:
  ButtonDemo();

  Pano::Button normal_disabled_button_;
  Pano::Button normal_enabled_button_;
  Pano::Button primary_disabled_button_;
  Pano::Button primary_enabled_button_;
  Pano::Button secondary_disabled_button_;
  Pano::Button secondary_enabled_button_;

  Pano::Frame normal_disabled_frame_;
  Pano::Frame normal_enabled_frame_;
  Pano::Frame primary_disabled_frame_;
  Pano::Frame primary_enabled_frame_;
  Pano::Frame secondary_disabled_frame_;
  Pano::Frame secondary_enabled_frame_;
};

#endif  // SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_BUTTON_H_
