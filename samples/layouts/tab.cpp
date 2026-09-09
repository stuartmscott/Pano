// Copyright 2026 Stuart Scott
#include <Pano/tab.h>
#include <PanoLayoutDemo/tab.h>

using namespace Pano;

TabDemo::TabDemo() : EdgeLayout() {
  const auto colors{App::current_->GetColorProvider()};
  const auto text_color{colors->GetColor(
      Significance::Normal,
      Condition::Enabled | Condition::Focused | Condition::Activated,
      Layer::Foreground)};

  text1_.SetColor(Layer::Foreground, text_color);
  text1_.SetColor(Layer::Background, Palette[0]);
  text1_.SetTextAlignment(TextAlignment::Center);
  text1_.SetVerticalAlignment(Alignment::Center);

  text2_.SetColor(Layer::Foreground, text_color);
  text2_.SetColor(Layer::Background, Palette[1]);
  text2_.SetTextAlignment(TextAlignment::Center);
  text2_.SetVerticalAlignment(Alignment::Center);

  text3_.SetColor(Layer::Foreground, text_color);
  text3_.SetColor(Layer::Background, Palette[2]);
  text3_.SetTextAlignment(TextAlignment::Center);
  text3_.SetVerticalAlignment(Alignment::Center);

  text4_.SetColor(Layer::Foreground, text_color);
  text4_.SetColor(Layer::Background, Palette[3]);
  text4_.SetTextAlignment(TextAlignment::Center);
  text4_.SetVerticalAlignment(Alignment::Center);

  tabs_.AddTab("1", &text1_);
  tabs_.AddTab("2", &text2_);
  tabs_.AddTab("3", &text3_);
  tabs_.AddTab("4", &text4_);

  frame_.SetView(&tabs_);
  frame_.SetMargin(10);

  SetView(Location::Center, &frame_);

  radio_label_.SetVerticalAlignment(Alignment::Center);
  radio_label_.SetTextAlignment(TextAlignment::Center);
  radio_label_.SetTextTruncation(TextTruncation::Ellipsis);
  radio_label_.SetTextWrap(TextWrap::None);
  grid_.SetView(0, 0, &radio_label_);

  radio_.OnChanged = [&](std::string s) {
    tabs_.SetTabLocation(Locations.at(s));
  };
  grid_.SetView(0, 1, &radio_, 1, 4);

  SetView(Location::Bottom, &grid_);
}
