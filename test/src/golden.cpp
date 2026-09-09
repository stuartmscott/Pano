// Copyright 2026 Stuart Scott
#include <Pano/button.h>
#include <Pano/checkbox.h>
#include <Pano/radio.h>
#include <Pano/tab.h>
#include <Pano/text.h>
#include <PanoTest/app.h>
#include <PanoTest/golden.h>
#include <gtest/gtest.h>

#include <vector>

namespace Pano::Test {

const std::vector<Alignment> Alignments{
    {Alignment::Start, Alignment::Center, Alignment::End}};
const std::vector<Condition> Conditions{
    {Condition::Disabled, Condition::Enabled,
     Condition::Enabled | Condition::Focused,
     Condition::Enabled | Condition::Activated,
     Condition::Enabled | Condition::Focused | Condition::Activated}};
const std::vector<Location> Locations{
    {Location::Top, Location::Bottom, Location::Left, Location::Right}};
const std::vector<Significance> Significances{
    {Significance::Primary, Significance::Secondary, Significance::Normal}};
const std::vector<TextAlignment> TextAlignments{
    {TextAlignment::Start, TextAlignment::Center, TextAlignment::End,
     TextAlignment::Justify}};
const std::vector<TextStyle> TextStyles{
    {TextStyle::Regular, TextStyle::Bold, TextStyle::Italic,
     TextStyle::BoldItalic, TextStyle::Monospace}};
const std::vector<TextTruncation> TextTruncations{
    {TextTruncation::None, TextTruncation::Clip, TextTruncation::Ellipsis}};
const std::vector<TextWrap> TextWraps{
    {TextWrap::None, TextWrap::Character, TextWrap::Word}};

TEST_F(AppTest, Golden_Button) {
  Window window("Golden", 200, 50);
  Button b{"Button"};
  window.SetContent(&b);
  for (const auto s : Significances) {
    b.SetSignificance(s);
    for (const auto c : Conditions) {
      b.SetCondition(c);
      const auto filename =
          "Button_" + ToString(s) + "_" + ToString(c) + ".png";
      window.Snapshot(filename);
      CheckGolden(filename);
    }
  }
}

TEST_F(AppTest, Golden_CheckBox) {
  Window window("Golden", 200, 50);
  CheckBox cb{"CheckBox"};
  window.SetContent(&cb);
  for (const auto s : Significances) {
    cb.SetSignificance(s);
    for (const auto c : Conditions) {
      cb.SetCondition(c);
      {
        const auto filename =
            "CheckBox_" + ToString(s) + "_" + ToString(c) + "_Checked.png";
        cb.SetChecked(true);
        window.Snapshot(filename);
        CheckGolden(filename);
      }
      {
        const auto filename =
            "CheckBox_" + ToString(s) + "_" + ToString(c) + "_Unchecked.png";
        cb.SetChecked(false);
        window.Snapshot(filename);
        CheckGolden(filename);
      }
    }
  }
}

TEST_F(AppTest, Golden_RadioButton) {
  Window window("Golden", 200, 50);
  RadioButton rb{nullptr, "Radio"};
  window.SetContent(&rb);
  for (const auto s : Significances) {
    rb.SetSignificance(s);
    for (const auto c : Conditions) {
      rb.SetCondition(c);
      {
        const auto filename =
            "RadioButton_" + ToString(s) + "_" + ToString(c) + "_Selected.png";
        rb.SetSelected(true);
        window.Snapshot(filename);
        CheckGolden(filename);
      }
      {
        const auto filename = "RadioButton_" + ToString(s) + "_" + ToString(c) +
                              "_Unselected.png";
        rb.SetSelected(false);
        window.Snapshot(filename);
        CheckGolden(filename);
      }
    }
  }
}

TEST_F(AppTest, Golden_RadioGroup) {
  Window window("Golden", 400, 50);
  RadioGroup rg{{"Radio A", "Radio B", "Radio C"}};
  window.SetContent(&rg);
  for (const auto s : Significances) {
    rg.SetSignificance(s);
    for (const auto c : {Condition::Disabled, Condition::Enabled}) {
      rg.SetCondition(c);
      {
        rg.SetAxis(Axis::X);
        window.SetSize({400, 50});
        const auto filename =
            "RadioGroup_" + ToString(s) + "_" + ToString(c) + "_Horizontal_";
        rg.SetSelectedRadio("Radio A");
        window.Snapshot(filename + "A.png");
        CheckGolden(filename + "A.png");
        rg.SetSelectedRadio("Radio B");
        window.Snapshot(filename + "B.png");
        CheckGolden(filename + "B.png");
        rg.SetSelectedRadio("Radio C");
        window.Snapshot(filename + "C.png");
        CheckGolden(filename + "C.png");
      }
      {
        rg.SetAxis(Axis::Y);
        window.SetSize({200, 150});
        const auto filename =
            "RadioGroup_" + ToString(s) + "_" + ToString(c) + "_Vertical_";
        rg.SetSelectedRadio("Radio A");
        window.Snapshot(filename + "A.png");
        CheckGolden(filename + "A.png");
        rg.SetSelectedRadio("Radio B");
        window.Snapshot(filename + "B.png");
        CheckGolden(filename + "B.png");
        rg.SetSelectedRadio("Radio C");
        window.Snapshot(filename + "C.png");
        CheckGolden(filename + "C.png");
      }
    }
  }
}

TEST_F(AppTest, Golden_TabLayout) {
  Window window("Golden", 200, 200);
  TabLayout tl;
  TextView t1{"Content A"};
  tl.AddTab("Tab A", &t1);
  TextView t2{"Content B"};
  tl.AddTab("Tab B", &t2);
  TextView t3{"Content C"};
  tl.AddTab("Tab C", &t3);
  window.SetContent(&tl);
  for (const auto s : Significances) {
    tl.SetSignificance(s);
    for (const auto c : {Condition::Disabled, Condition::Enabled}) {
      tl.SetCondition(c);
      for (const auto l : Locations) {
        const auto filename = "TabLayout_" + ToString(s) + "_" + ToString(c) +
                              "_" + ToString(l) + "_";
        tl.SetTabLocation(l);
        tl.SetSelectedTab(0);
        window.Snapshot(filename + "A.png");
        CheckGolden(filename + "A.png");
        tl.SetSelectedTab(1);
        window.Snapshot(filename + "B.png");
        CheckGolden(filename + "B.png");
        tl.SetSelectedTab(2);
        window.Snapshot(filename + "C.png");
        CheckGolden(filename + "C.png");
      }
    }
  }
}

TEST_F(AppTest, Golden_TextView) {
  Window window("Golden", 200, 200);
  TextView tv{
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod "
      "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "
      "veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
      "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "
      "velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "
      "occaecat cupidatat non proident, sunt in culpa qui officia deserunt "
      "mollit anim id est laborum."};
  window.SetContent(&tv);
  for (const auto s : Significances) {
    tv.SetSignificance(s);
    for (const auto c : {Condition::Disabled, Condition::Enabled}) {
      tv.SetCondition(c);
      for (const auto va : Alignments) {
        tv.SetVerticalAlignment(va);
        for (const auto ta : TextAlignments) {
          tv.SetTextAlignment(ta);
          for (const auto ts : TextStyles) {
            tv.SetTextStyle(ts);
            for (const auto tr : TextTruncations) {
              tv.SetTextTruncation(tr);
              for (const auto tw : TextWraps) {
                tv.SetTextWrap(tw);
                const auto filename =
                    "TextView_" + ToString(s) + "_" + ToString(c) + "_" +
                    ToString(va) + "_" + ToString(ta) + "_" + ToString(ts) +
                    "_" + ToString(tr) + "_" + ToString(tw) + ".png";
                window.Snapshot(filename);
                CheckGolden(filename);
              }
            }
          }
        }
      }
    }
  }
}
};  // namespace Pano::Test
