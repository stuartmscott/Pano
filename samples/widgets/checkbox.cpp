// Copyright 2026 Stuart Scott
#include <Pano/constants.h>
#include <PanoWidgetDemo/checkbox.h>

using namespace Pano;

CheckBoxDemo::CheckBoxDemo() : GridLayout(3, 2) {
  normal_disabled_check_.SetSignificance(Significance::Normal);
  normal_disabled_check_.SetCondition(Condition::Disabled);
  normal_disabled_check_.SetTextAlignment(TextAlignment::Center);
  normal_disabled_check_.SetVerticalAlignment(Alignment::Center);
  const auto normal_disabled_check_trigger = [&](bool checked) {
    normal_disabled_check_.SetText(std::string("Normal\n") +
                                   (checked ? "Checked" : "Unchecked"));
  };
  normal_disabled_check_.OnChanged = normal_disabled_check_trigger;
  normal_disabled_check_trigger(false);
  normal_disabled_frame_.SetMargin(10);
  normal_disabled_frame_.SetView(&normal_disabled_check_);
  SetView(0, 0, &normal_disabled_frame_);

  normal_enabled_check_.SetSignificance(Significance::Normal);
  normal_enabled_check_.SetTextAlignment(TextAlignment::Center);
  normal_enabled_check_.SetVerticalAlignment(Alignment::Center);
  const auto normal_enabled_check_trigger = [&](bool checked) {
    normal_enabled_check_.SetText(std::string("Normal\n") +
                                  (checked ? "Checked" : "Unchecked"));
  };
  normal_enabled_check_.OnChanged = normal_enabled_check_trigger;
  normal_enabled_check_trigger(false);
  normal_enabled_frame_.SetMargin(10);
  normal_enabled_frame_.SetView(&normal_enabled_check_);
  SetView(0, 1, &normal_enabled_frame_);

  primary_disabled_check_.SetSignificance(Significance::Primary);
  primary_disabled_check_.SetCondition(Condition::Disabled);
  primary_disabled_check_.SetTextAlignment(TextAlignment::Center);
  primary_disabled_check_.SetVerticalAlignment(Alignment::Center);
  const auto primary_disabled_check_trigger = [&](bool checked) {
    primary_disabled_check_.SetText(std::string("Primary\n") +
                                    (checked ? "Checked" : "Unchecked"));
  };
  primary_disabled_check_.OnChanged = primary_disabled_check_trigger;
  primary_disabled_check_trigger(false);
  primary_disabled_frame_.SetMargin(10);
  primary_disabled_frame_.SetView(&primary_disabled_check_);
  SetView(1, 0, &primary_disabled_frame_);

  primary_enabled_check_.SetSignificance(Significance::Primary);
  primary_enabled_check_.SetTextAlignment(TextAlignment::Center);
  primary_enabled_check_.SetVerticalAlignment(Alignment::Center);
  const auto primary_enabled_check_trigger = [&](bool checked) {
    primary_enabled_check_.SetText(std::string("Primary\n") +
                                   (checked ? "Checked" : "Unchecked"));
  };
  primary_enabled_check_.OnChanged = primary_enabled_check_trigger;
  primary_enabled_check_trigger(false);
  primary_enabled_frame_.SetMargin(10);
  primary_enabled_frame_.SetView(&primary_enabled_check_);
  SetView(1, 1, &primary_enabled_frame_);

  secondary_disabled_check_.SetSignificance(Significance::Secondary);
  secondary_disabled_check_.SetCondition(Condition::Disabled);
  secondary_disabled_check_.SetTextAlignment(TextAlignment::Center);
  secondary_disabled_check_.SetVerticalAlignment(Alignment::Center);
  const auto secondary_disabled_check_trigger = [&](bool checked) {
    secondary_disabled_check_.SetText(std::string("Secondary\n") +
                                      (checked ? "Checked" : "Unchecked"));
  };
  secondary_disabled_check_.OnChanged = secondary_disabled_check_trigger;
  secondary_disabled_check_trigger(false);
  secondary_disabled_frame_.SetMargin(10);
  secondary_disabled_frame_.SetView(&secondary_disabled_check_);
  SetView(2, 0, &secondary_disabled_frame_);

  secondary_enabled_check_.SetSignificance(Significance::Secondary);
  secondary_enabled_check_.SetTextAlignment(TextAlignment::Center);
  secondary_enabled_check_.SetVerticalAlignment(Alignment::Center);
  const auto secondary_enabled_check_trigger = [&](bool checked) {
    secondary_enabled_check_.SetText(std::string("Secondary\n") +
                                     (checked ? "Checked" : "Unchecked"));
  };
  secondary_enabled_check_.OnChanged = secondary_enabled_check_trigger;
  secondary_enabled_check_trigger(false);
  secondary_enabled_frame_.SetMargin(10);
  secondary_enabled_frame_.SetView(&secondary_enabled_check_);
  SetView(2, 1, &secondary_enabled_frame_);
}
