// Copyright 2026 Stuart Scott
#include <Pano/color.h>
#include <PanoMaterialColor/provider.h>
#include <SDL3/SDL.h>

using namespace Pano;

ColorProvider* CreateDarkMaterialColorProvider() {
  //            Foreground  Background
  // Primary    #BB86FC     Gray
  // Secondary  #03DAC6     Gray
  // Normal     Gray_B      Gray_1

  const SDL_Color primary{0xBB, 0x86, 0xFC, 0xFF};
  const SDL_Color secondary{0x03, 0xDA, 0xC6, 0xFF};
  const SDL_Color disabled_fg{Color::Gray_7};
  const SDL_Color disabled_bg{Color::Gray_3};
  const SDL_Color normal_fg{Color::Gray_B};
  const SDL_Color normal_bg{Color::Gray_1};
  const SDL_Color normal_focused_fg{Color::Gray_C};
  const SDL_Color normal_focused_bg{Color::Gray_2};
  const SDL_Color normal_activated_fg{Color::Gray_D};
  const SDL_Color normal_activated_bg{Color::Gray_3};
  const SDL_Color normal_focused_activated_fg{Color::Gray_E};
  const SDL_Color normal_focused_activated_bg{Color::Gray_4};
  const SDL_Color error{0xCF, 0x66, 0x79, 0xFF};

  const auto p{new ColorProvider()};

  // Primary
  p->SetColor(Significance::Primary, Condition::Disabled, Layer::Foreground,
              disabled_fg);
  p->SetColor(Significance::Primary, Condition::Disabled, Layer::Background,
              disabled_bg);
  p->SetColor(Significance::Primary, Condition::Enabled, Layer::Foreground,
              primary);
  p->SetColor(Significance::Primary, Condition::Enabled, Layer::Background,
              normal_bg);
  p->SetColor(Significance::Primary, Condition::Enabled | Condition::Focused,
              Layer::Foreground, primary);
  p->SetColor(Significance::Primary, Condition::Enabled | Condition::Focused,
              Layer::Background, normal_focused_bg);
  p->SetColor(Significance::Primary, Condition::Enabled | Condition::Activated,
              Layer::Foreground, primary);
  p->SetColor(Significance::Primary, Condition::Enabled | Condition::Activated,
              Layer::Background, normal_activated_bg);
  p->SetColor(Significance::Primary,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Foreground, primary);
  p->SetColor(Significance::Primary,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Background, normal_focused_activated_bg);

  // Secondary
  p->SetColor(Significance::Secondary, Condition::Disabled, Layer::Foreground,
              disabled_fg);
  p->SetColor(Significance::Secondary, Condition::Disabled, Layer::Background,
              disabled_bg);
  p->SetColor(Significance::Secondary, Condition::Enabled, Layer::Foreground,
              secondary);
  p->SetColor(Significance::Secondary, Condition::Enabled, Layer::Background,
              normal_bg);
  p->SetColor(Significance::Secondary, Condition::Enabled | Condition::Focused,
              Layer::Foreground, secondary);
  p->SetColor(Significance::Secondary, Condition::Enabled | Condition::Focused,
              Layer::Background, normal_focused_bg);
  p->SetColor(Significance::Secondary,
              Condition::Enabled | Condition::Activated, Layer::Foreground,
              secondary);
  p->SetColor(Significance::Secondary,
              Condition::Enabled | Condition::Activated, Layer::Background,
              normal_activated_bg);
  p->SetColor(Significance::Secondary,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Foreground, secondary);
  p->SetColor(Significance::Secondary,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Background, normal_focused_activated_bg);

  // Normal
  p->SetColor(Significance::Normal, Condition::Disabled, Layer::Foreground,
              disabled_fg);
  p->SetColor(Significance::Normal, Condition::Disabled, Layer::Background,
              disabled_bg);
  p->SetColor(Significance::Normal, Condition::Enabled, Layer::Foreground,
              normal_fg);
  p->SetColor(Significance::Normal, Condition::Enabled, Layer::Background,
              normal_bg);
  p->SetColor(Significance::Normal, Condition::Enabled | Condition::Focused,
              Layer::Foreground, normal_focused_fg);
  p->SetColor(Significance::Normal, Condition::Enabled | Condition::Focused,
              Layer::Background, normal_focused_bg);
  p->SetColor(Significance::Normal, Condition::Enabled | Condition::Activated,
              Layer::Foreground, normal_activated_fg);
  p->SetColor(Significance::Normal, Condition::Enabled | Condition::Activated,
              Layer::Background, normal_activated_bg);
  p->SetColor(Significance::Normal,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Foreground, normal_focused_activated_fg);
  p->SetColor(Significance::Normal,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Background, normal_focused_activated_bg);

  // Text
  p->SetColor(Significance::TextTitle, Condition::Disabled, Layer::Foreground,
              disabled_fg);
  p->SetColor(Significance::TextTitle, Condition::Disabled, Layer::Background,
              disabled_bg);
  p->SetColor(Significance::TextTitle, Condition::Enabled, Layer::Foreground,
              primary);
  p->SetColor(Significance::TextTitle, Condition::Enabled, Layer::Background,
              normal_bg);
  p->SetColor(Significance::TextTitle, Condition::Enabled | Condition::Focused,
              Layer::Foreground, primary);
  p->SetColor(Significance::TextTitle, Condition::Enabled | Condition::Focused,
              Layer::Background, normal_focused_bg);
  p->SetColor(Significance::TextTitle,
              Condition::Enabled | Condition::Activated, Layer::Foreground,
              primary);
  p->SetColor(Significance::TextTitle,
              Condition::Enabled | Condition::Activated, Layer::Background,
              normal_activated_bg);
  p->SetColor(Significance::TextTitle,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Foreground, primary);
  p->SetColor(Significance::TextTitle,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Background, normal_focused_activated_bg);
  for (const auto t : {
           Significance::TextHeading1,
           Significance::TextHeading2,
           Significance::TextHeading3,
           Significance::TextHeading4,
           Significance::TextHeading5,
           Significance::TextHeading6,
           Significance::TextSubtitle,
           Significance::TextBody,
           Significance::TextCaption,
       }) {
    p->SetColor(t, Condition::Disabled, Layer::Foreground, disabled_fg);
    p->SetColor(t, Condition::Disabled, Layer::Background, disabled_bg);
    p->SetColor(t, Condition::Enabled, Layer::Foreground, normal_fg);
    p->SetColor(t, Condition::Enabled, Layer::Background, normal_bg);
    p->SetColor(t, Condition::Enabled | Condition::Focused, Layer::Foreground,
                normal_focused_fg);
    p->SetColor(t, Condition::Enabled | Condition::Focused, Layer::Background,
                normal_focused_bg);
    p->SetColor(t, Condition::Enabled | Condition::Activated, Layer::Foreground,
                normal_activated_fg);
    p->SetColor(t, Condition::Enabled | Condition::Activated, Layer::Background,
                normal_activated_bg);
    p->SetColor(t,
                Condition::Enabled | Condition::Focused | Condition::Activated,
                Layer::Foreground, normal_focused_activated_fg);
    p->SetColor(t,
                Condition::Enabled | Condition::Focused | Condition::Activated,
                Layer::Background, normal_focused_activated_bg);
  }

  // Error
  p->SetColor(Significance::Error, Condition::Enabled, Layer::Foreground,
              normal_fg);
  p->SetColor(Significance::Error, Condition::Enabled, Layer::Background,
              error);

  // Danger
  p->SetColor(Significance::Danger, Condition::Enabled, Layer::Foreground,
              normal_fg);
  p->SetColor(Significance::Danger, Condition::Enabled, Layer::Background,
              error);
  p->SetColor(Significance::Danger, Condition::Enabled | Condition::Focused,
              Layer::Foreground, normal_focused_fg);
  p->SetColor(Significance::Danger, Condition::Enabled | Condition::Focused,
              Layer::Background, error);
  p->SetColor(Significance::Danger, Condition::Enabled | Condition::Activated,
              Layer::Foreground, normal_activated_fg);
  p->SetColor(Significance::Danger, Condition::Enabled | Condition::Activated,
              Layer::Background, error);
  p->SetColor(Significance::Danger,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Foreground, normal_focused_activated_fg);
  p->SetColor(Significance::Danger,
              Condition::Enabled | Condition::Focused | Condition::Activated,
              Layer::Background, error);
  return p;
}
