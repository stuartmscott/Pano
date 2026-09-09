// Copyright 2026 Stuart Scott
#include <Pano/app.h>
#include <Pano/button.h>
#include <Pano/edge.h>
#include <Pano/grid.h>
#include <Pano/icon.h>
#include <Pano/log.h>
#include <Pano/stack.h>
#include <Pano/tab.h>
#include <Pano/text.h>
#include <Pano/window.h>
#include <PanoLayoutDemo/edge.h>
#include <PanoLayoutDemo/grid.h>
#include <PanoLayoutDemo/stack.h>
#include <PanoLayoutDemo/tab.h>
#include <PanoMaterialColor/provider.h>
#include <PanoMaterialIcon/provider.h>
#include <PanoNotoSans/provider.h>

#include <iostream>
#include <string>

using namespace Pano;

int main(int argc, char* argv[]) {
  App app;
  app.SetColorProvider(CreateLightMaterialColorProvider());
  app.SetFontProvider(CreateNotoSansProvider());
  app.SetIconProvider(CreateMaterialIconProvider());
  Window window("Pano Layout Demo");
  TabLayout layout;
  EdgeDemo edge;
  layout.AddTab("Edge", &edge);
  GridDemo grid;
  layout.AddTab("Grid", &grid);
  StackDemo stack;
  layout.AddTab("Stack", &stack);
  TabDemo tab;
  layout.AddTab("Tab", &tab);
  window.SetContent(&layout);
  window.SetVisible(true);
  app.Start();
  return 0;
}
