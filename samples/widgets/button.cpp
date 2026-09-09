// Copyright 2026 Stuart Scott
#include <Pano/constants.h>
#include <PanoWidgetDemo/button.h>

using namespace Pano;

ButtonDemo::ButtonDemo() : GridLayout(3, 2) {
  normal_disabled_button_.SetSignificance(Significance::Normal);
  normal_disabled_button_.SetCondition(Condition::Disabled);
  normal_disabled_button_.SetTextAlignment(TextAlignment::Center);
  normal_disabled_button_.SetVerticalAlignment(Alignment::Center);
  const auto normal_disabled_button_trigger = [&]() {
    normal_disabled_button_.SetText(
        "Normal\n" + ToString(normal_disabled_button_.GetCondition()));
  };
  normal_disabled_button_.OnMouseFocusGained = normal_disabled_button_trigger;
  normal_disabled_button_.OnMouseFocusLost = normal_disabled_button_trigger;
  normal_disabled_button_.OnPressed = normal_disabled_button_trigger;
  normal_disabled_button_.OnReleased = normal_disabled_button_trigger;
  normal_disabled_button_trigger();
  normal_disabled_frame_.SetMargin(10);
  normal_disabled_frame_.SetView(&normal_disabled_button_);
  SetView(0, 0, &normal_disabled_frame_);

  normal_enabled_button_.SetSignificance(Significance::Normal);
  normal_enabled_button_.SetTextAlignment(TextAlignment::Center);
  normal_enabled_button_.SetVerticalAlignment(Alignment::Center);
  const auto normal_enabled_button_trigger = [&]() {
    normal_enabled_button_.SetText(
        "Normal\n" + ToString(normal_enabled_button_.GetCondition()));
  };
  normal_enabled_button_.OnMouseFocusGained = normal_enabled_button_trigger;
  normal_enabled_button_.OnMouseFocusLost = normal_enabled_button_trigger;
  normal_enabled_button_.OnPressed = normal_enabled_button_trigger;
  normal_enabled_button_.OnReleased = normal_enabled_button_trigger;
  normal_enabled_button_trigger();
  normal_enabled_frame_.SetMargin(10);
  normal_enabled_frame_.SetView(&normal_enabled_button_);
  SetView(0, 1, &normal_enabled_frame_);

  primary_disabled_button_.SetSignificance(Significance::Primary);
  primary_disabled_button_.SetCondition(Condition::Disabled);
  primary_disabled_button_.SetTextAlignment(TextAlignment::Center);
  primary_disabled_button_.SetVerticalAlignment(Alignment::Center);
  const auto primary_disabled_button_trigger = [&]() {
    primary_disabled_button_.SetText(
        "Primary\n" + ToString(primary_disabled_button_.GetCondition()));
  };
  primary_disabled_button_.OnMouseFocusGained = primary_disabled_button_trigger;
  primary_disabled_button_.OnMouseFocusLost = primary_disabled_button_trigger;
  primary_disabled_button_.OnPressed = primary_disabled_button_trigger;
  primary_disabled_button_.OnReleased = primary_disabled_button_trigger;
  primary_disabled_button_trigger();
  primary_disabled_frame_.SetMargin(10);
  primary_disabled_frame_.SetView(&primary_disabled_button_);
  SetView(1, 0, &primary_disabled_frame_);

  primary_enabled_button_.SetSignificance(Significance::Primary);
  primary_enabled_button_.SetTextAlignment(TextAlignment::Center);
  primary_enabled_button_.SetVerticalAlignment(Alignment::Center);
  const auto primary_enabled_button_trigger = [&]() {
    primary_enabled_button_.SetText(
        "Primary\n" + ToString(primary_enabled_button_.GetCondition()));
  };
  primary_enabled_button_.OnMouseFocusGained = primary_enabled_button_trigger;
  primary_enabled_button_.OnMouseFocusLost = primary_enabled_button_trigger;
  primary_enabled_button_.OnPressed = primary_enabled_button_trigger;
  primary_enabled_button_.OnReleased = primary_enabled_button_trigger;
  primary_enabled_button_trigger();
  primary_enabled_frame_.SetMargin(10);
  primary_enabled_frame_.SetView(&primary_enabled_button_);
  SetView(1, 1, &primary_enabled_frame_);

  secondary_disabled_button_.SetSignificance(Significance::Secondary);
  secondary_disabled_button_.SetCondition(Condition::Disabled);
  secondary_disabled_button_.SetTextAlignment(TextAlignment::Center);
  secondary_disabled_button_.SetVerticalAlignment(Alignment::Center);
  const auto secondary_disabled_button_trigger = [&]() {
    secondary_disabled_button_.SetText(
        "Secondary\n" + ToString(secondary_disabled_button_.GetCondition()));
  };
  secondary_disabled_button_.OnMouseFocusGained =
      secondary_disabled_button_trigger;
  secondary_disabled_button_.OnMouseFocusLost =
      secondary_disabled_button_trigger;
  secondary_disabled_button_.OnPressed = secondary_disabled_button_trigger;
  secondary_disabled_button_.OnReleased = secondary_disabled_button_trigger;
  secondary_disabled_button_trigger();
  secondary_disabled_frame_.SetMargin(10);
  secondary_disabled_frame_.SetView(&secondary_disabled_button_);
  SetView(2, 0, &secondary_disabled_frame_);

  secondary_enabled_button_.SetSignificance(Significance::Secondary);
  secondary_enabled_button_.SetTextAlignment(TextAlignment::Center);
  secondary_enabled_button_.SetVerticalAlignment(Alignment::Center);
  const auto secondary_enabled_button_trigger = [&]() {
    secondary_enabled_button_.SetText(
        "Secondary\n" + ToString(secondary_enabled_button_.GetCondition()));
  };
  secondary_enabled_button_.OnMouseFocusGained =
      secondary_enabled_button_trigger;
  secondary_enabled_button_.OnMouseFocusLost = secondary_enabled_button_trigger;
  secondary_enabled_button_.OnPressed = secondary_enabled_button_trigger;
  secondary_enabled_button_.OnReleased = secondary_enabled_button_trigger;
  secondary_enabled_button_trigger();
  secondary_enabled_frame_.SetMargin(10);
  secondary_enabled_frame_.SetView(&secondary_enabled_button_);
  SetView(2, 1, &secondary_enabled_frame_);
}
