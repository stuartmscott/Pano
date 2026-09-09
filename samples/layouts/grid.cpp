// Copyright 2026 Stuart Scott
#include <Pano/grid.h>
#include <PanoLayoutDemo/grid.h>

using namespace Pano;

GridDemo::GridDemo() : GridLayout(4, 5) {
  const auto colors{App::current_->GetColorProvider()};
  const auto text_color{colors->GetColor(
      Significance::Normal,
      Condition::Enabled | Condition::Focused | Condition::Activated,
      Layer::Foreground)};
  int i = 0;
  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 5; ++c) {
      const auto t =
          new TextView("Cell " + std::to_string(r) + ',' + std::to_string(c));
      t->SetColor(Layer::Foreground, text_color);
      t->SetColor(Layer::Background, Palette[i++ % 4]);
      t->SetTextAlignment(TextAlignment::Center);
      t->SetVerticalAlignment(Alignment::Center);
      SetView(r, c, t);
    }
  }
}
