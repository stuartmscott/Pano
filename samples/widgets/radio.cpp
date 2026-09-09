// Copyright 2026 Stuart Scott
#include <Pano/constants.h>
#include <PanoWidgetDemo/radio.h>

using namespace Pano;

RadioGroupDemo::RadioGroupDemo() : GridLayout(3, 2) {
  normal_disabled_radio_.SetAxis(Axis::Y);
  normal_disabled_radio_.SetSignificance(Significance::Normal);
  normal_disabled_radio_.SetCondition(Condition::Disabled);
  normal_disabled_radio_.SetTextAlignment(TextAlignment::Center);
  normal_disabled_radio_.SetVerticalAlignment(Alignment::Center);
  normal_disabled_frame_.SetMargin(10);
  normal_disabled_frame_.SetView(&normal_disabled_radio_);
  SetView(0, 0, &normal_disabled_frame_);

  normal_enabled_radio_.SetAxis(Axis::Y);
  normal_enabled_radio_.SetSignificance(Significance::Normal);
  normal_enabled_radio_.SetTextAlignment(TextAlignment::Center);
  normal_enabled_radio_.SetVerticalAlignment(Alignment::Center);
  normal_enabled_frame_.SetMargin(10);
  normal_enabled_frame_.SetView(&normal_enabled_radio_);
  SetView(0, 1, &normal_enabled_frame_);

  primary_disabled_radio_.SetAxis(Axis::Y);
  primary_disabled_radio_.SetSignificance(Significance::Primary);
  primary_disabled_radio_.SetCondition(Condition::Disabled);
  primary_disabled_radio_.SetTextAlignment(TextAlignment::Center);
  primary_disabled_radio_.SetVerticalAlignment(Alignment::Center);
  primary_disabled_frame_.SetMargin(10);
  primary_disabled_frame_.SetView(&primary_disabled_radio_);
  SetView(1, 0, &primary_disabled_frame_);

  primary_enabled_radio_.SetAxis(Axis::Y);
  primary_enabled_radio_.SetSignificance(Significance::Primary);
  primary_enabled_radio_.SetTextAlignment(TextAlignment::Center);
  primary_enabled_radio_.SetVerticalAlignment(Alignment::Center);
  primary_enabled_frame_.SetMargin(10);
  primary_enabled_frame_.SetView(&primary_enabled_radio_);
  SetView(1, 1, &primary_enabled_frame_);

  secondary_disabled_radio_.SetAxis(Axis::Y);
  secondary_disabled_radio_.SetSignificance(Significance::Secondary);
  secondary_disabled_radio_.SetCondition(Condition::Disabled);
  secondary_disabled_radio_.SetTextAlignment(TextAlignment::Center);
  secondary_disabled_radio_.SetVerticalAlignment(Alignment::Center);
  secondary_disabled_frame_.SetMargin(10);
  secondary_disabled_frame_.SetView(&secondary_disabled_radio_);
  SetView(2, 0, &secondary_disabled_frame_);

  secondary_enabled_radio_.SetAxis(Axis::Y);
  secondary_enabled_radio_.SetSignificance(Significance::Secondary);
  secondary_enabled_radio_.SetTextAlignment(TextAlignment::Center);
  secondary_enabled_radio_.SetVerticalAlignment(Alignment::Center);
  secondary_enabled_frame_.SetMargin(10);
  secondary_enabled_frame_.SetView(&secondary_enabled_radio_);
  SetView(2, 1, &secondary_enabled_frame_);
}
