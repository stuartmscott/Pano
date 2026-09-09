// Copyright 2026 Stuart Scott
#ifndef SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_RADIO_H_
#define SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_RADIO_H_

#include <Pano/frame.h>
#include <Pano/grid.h>
#include <Pano/radio.h>

#include <string>

class RadioGroupDemo : public Pano::GridLayout {
 public:
  RadioGroupDemo();

  Pano::RadioGroup normal_disabled_radio_{{"Normal A", "Normal B", "Normal C"}};
  Pano::RadioGroup normal_enabled_radio_{{"Normal A", "Normal B", "Normal C"}};
  Pano::RadioGroup primary_disabled_radio_{
      {"Primary A", "Primary B", "Primary C"}};
  Pano::RadioGroup primary_enabled_radio_{
      {"Primary A", "Primary B", "Primary C"}};
  Pano::RadioGroup secondary_disabled_radio_{
      {"Secondary A", "Secondary B", "Secondary C"}};
  Pano::RadioGroup secondary_enabled_radio_{
      {"Secondary A", "Secondary B", "Secondary C"}};

  Pano::Frame normal_disabled_frame_;
  Pano::Frame normal_enabled_frame_;
  Pano::Frame primary_disabled_frame_;
  Pano::Frame primary_enabled_frame_;
  Pano::Frame secondary_disabled_frame_;
  Pano::Frame secondary_enabled_frame_;
};

#endif  // SAMPLES_WIDGETS_INCLUDE_PANOWIDGETDEMO_RADIO_H_
