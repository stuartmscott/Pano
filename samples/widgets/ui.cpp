// Copyright 2026 Stuart Scott
#include <Pano/app.h>
#include <Pano/button.h>
#include <Pano/log.h>
#include <Pano/tab.h>
#include <Pano/window.h>
#include <PanoMaterialColor/provider.h>
#include <PanoMaterialIcon/provider.h>
#include <PanoNotoSans/provider.h>
#include <PanoWidgetDemo/button.h>
#include <PanoWidgetDemo/checkbox.h>
#include <PanoWidgetDemo/radio.h>

#include <iostream>
#include <string>

using namespace Pano;

int main(int argc, char* argv[]) {
  App app;
  // app.SetColorProvider(CreateDarkMaterialColorProvider());
  app.SetColorProvider(CreateLightMaterialColorProvider());
  app.SetFontProvider(CreateNotoSansProvider());
  app.SetIconProvider(CreateMaterialIconProvider());
  Window window("Pano Widget Demo");
  TabLayout layout;
  ButtonDemo button;
  layout.AddTab("Button", &button);
  CheckBoxDemo checkbox;
  layout.AddTab("CheckBox", &checkbox);
  RadioGroupDemo radiogroup;
  layout.AddTab("RadioGroup", &radiogroup);
  window.SetContent(&layout);
  window.SetVisible(true);
  app.Start();
  return 0;
}
