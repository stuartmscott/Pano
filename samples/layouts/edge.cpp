// Copyright 2026 Stuart Scott
#include <Pano/edge.h>
#include <PanoLayoutDemo/edge.h>

using namespace Pano;

EdgeDemo::EdgeDemo() : EdgeLayout() {
  const auto colors{App::current_->GetColorProvider()};
  const auto text_color{colors->GetColor(
      Significance::Normal,
      Condition::Enabled | Condition::Focused | Condition::Activated,
      Layer::Foreground)};

  top_.SetColor(Layer::Foreground, text_color);
  top_.SetColor(Layer::Background, {0xD2, 0x50, 0x50, 0xFF});
  top_.SetTextAlignment(TextAlignment::Center);
  top_.SetVerticalAlignment(Alignment::Center);

  bottom_.SetColor(Layer::Foreground, text_color);
  bottom_.SetColor(Layer::Background, {0x82, 0xB4, 0x82, 0xFF});
  bottom_.SetTextAlignment(TextAlignment::Center);
  bottom_.SetVerticalAlignment(Alignment::Center);

  left_.SetColor(Layer::Foreground, text_color);
  left_.SetColor(Layer::Background, {0x64, 0x8C, 0xD2, 0xFF});
  left_.SetTextAlignment(TextAlignment::Center);
  left_.SetVerticalAlignment(Alignment::Center);

  right_.SetColor(Layer::Foreground, text_color);
  right_.SetColor(Layer::Background, {0xFF, 0xFF, 0xB4, 0xFF});
  right_.SetTextAlignment(TextAlignment::Center);
  right_.SetVerticalAlignment(Alignment::Center);

  center_.SetColor(Layer::Foreground, text_color);
  center_.SetColor(Layer::Background,
                   colors->GetColor(Significance::Normal, Condition::Enabled,
                                    Layer::Background));
  center_.SetTextAlignment(TextAlignment::Center);
  center_.SetVerticalAlignment(Alignment::Center);

  SetView(Location::Top, &top_);
  SetView(Location::Bottom, &bottom_);
  SetView(Location::Left, &left_);
  SetView(Location::Right, &right_);
  SetView(Location::Center, &center_);
}
