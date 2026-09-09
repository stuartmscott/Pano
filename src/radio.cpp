// Copyright 2026 Stuart Scott
#include <Pano/radio.h>

#include <string>
#include <vector>

namespace Pano {

void RadioButton::setup() {
  SetIconLocation(Location::Left);
  OnPressed = [&]() { group_->SetSelectedRadio(GetText()); };
}

void RadioGroup::SetOptions(const std::vector<std::string> options) {
  ClearViews();

  options_ = options;

  if (options.empty()) {
    return;
  }

  for (const auto& o : options) {
    const auto b{new RadioButton(this, o)};
    buttons_[o] = b;
    AddView(b);
  }

  SetSelectedRadio(*(options.begin()));
}
};  // namespace Pano
