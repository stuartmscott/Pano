// Copyright 2026 Stuart Scott
#include <Pano/stack.h>
#include <PanoLayoutDemo/stack.h>

using namespace Pano;

StackDemo::StackDemo() : EdgeLayout() {
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

  stack_.AddView(&text1_);
  stack_.AddView(&text2_);
  stack_.AddView(&text3_);
  stack_.AddView(&text4_);

  frame_.SetView(&stack_);
  frame_.SetMargin(10);

  SetView(Location::Center, &frame_);

  radio_label_.SetVerticalAlignment(Alignment::Center);
  radio_label_.SetTextAlignment(TextAlignment::Center);
  radio_label_.SetTextTruncation(TextTruncation::Ellipsis);
  radio_label_.SetTextWrap(TextWrap::None);
  grid_.SetView(0, 0, &radio_label_);

  radio_.OnChanged = [&](std::string s) { stack_.SetAxis(Axes.at(s)); };
  grid_.SetView(0, 1, &radio_, 1, 3);

  SetView(Location::Bottom, &grid_);
}
