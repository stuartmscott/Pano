// Copyright 2026 Stuart Scott
#ifndef SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_CHECKBOX_H_
#define SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_CHECKBOX_H_

#include <Pano/checkbox.h>
#include <Pano/frame.h>
#include <Pano/grid.h>

#include <string>

class CheckBoxDemo : public Pano::GridLayout {
 public:
  CheckBoxDemo();

  Pano::CheckBox normal_disabled_check_;
  Pano::CheckBox normal_enabled_check_;
  Pano::CheckBox primary_disabled_check_;
  Pano::CheckBox primary_enabled_check_;
  Pano::CheckBox secondary_disabled_check_;
  Pano::CheckBox secondary_enabled_check_;

  Pano::Frame normal_disabled_frame_;
  Pano::Frame normal_enabled_frame_;
  Pano::Frame primary_disabled_frame_;
  Pano::Frame primary_enabled_frame_;
  Pano::Frame secondary_disabled_frame_;
  Pano::Frame secondary_enabled_frame_;
};

#endif  // SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_CHECKBOX_H_
