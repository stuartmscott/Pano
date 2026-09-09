// Copyright 2026 Stuart Scott
#include <Pano/checkbox.h>
#include <Pano/constants.h>
#include <Pano/log.h>
#include <SDL3/SDL.h>

namespace Pano {

void CheckBox::setup() {
  SetIconLocation(Location::Left);
  OnPressed = [&]() { SetChecked(!checked_); };
}
};  // namespace Pano
