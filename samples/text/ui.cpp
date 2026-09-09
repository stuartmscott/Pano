// Copyright 2026 Stuart Scott
#include <Pano/app.h>
#include <Pano/constants.h>
#include <Pano/edge.h>
#include <Pano/grid.h>
#include <Pano/radio.h>
#include <Pano/text.h>
#include <Pano/window.h>
#include <PanoMaterialColor/provider.h>
#include <PanoMaterialIcon/provider.h>
#include <PanoNotoSans/provider.h>

#include <iostream>
#include <map>
#include <string>

using namespace Pano;

const std::map<const std::string, const Alignment> VerticalAlignments{
    {"Start", Alignment::Start},
    {"Center", Alignment::Center},
    {"End", Alignment::End}};
const std::map<const std::string, const TextAlignment> TextAlignments{
    {"Start", TextAlignment::Start},
    {"Center", TextAlignment::Center},
    {"End", TextAlignment::End},
    {"Justify", TextAlignment::Justify}};
const std::map<const std::string, const TextTruncation> TextTruncations{
    {"None", TextTruncation::None},
    {"Clip", TextTruncation::Clip},
    {"Ellipsis", TextTruncation::Ellipsis}};
const std::map<const std::string, const TextWrap> TextWraps{
    {"None", TextWrap::None},
    {"Character", TextWrap::Character},
    {"Word", TextWrap::Word}};

int main(int argc, char* argv[]) {
  App app;
  app.SetColorProvider(CreateLightMaterialColorProvider());
  app.SetFontProvider(CreateNotoSansProvider());
  app.SetIconProvider(CreateMaterialIconProvider());
  Window window("Pano Text Demo");

  TextEntry entry("Hello!");
  entry.SetVerticalAlignment(Alignment::Center);
  entry.SetTextAlignment(TextAlignment::Center);
  entry.SetTextTruncation(TextTruncation::Ellipsis);
  entry.SetTextWrap(TextWrap::Word);
  entry.SetTextSize(100);

  RadioGroup vertical_alignment{
      {"Start", "Center", "End"}, [&](std::string s) {
        entry.SetVerticalAlignment(VerticalAlignments.at(s));
      }};
  vertical_alignment.SetSelectedRadio("Center");
  RadioGroup text_alignment{
      {"Start", "Center", "End", "Justify"},
      [&](std::string s) { entry.SetTextAlignment(TextAlignments.at(s)); }};
  text_alignment.SetSelectedRadio("Center");
  RadioGroup text_truncation{{"None", "Clip", "Ellipsis"}, [&](std::string s) {
                               entry.SetTextTruncation(TextTruncations.at(s));
                             }};
  text_truncation.SetSelectedRadio("Ellipsis");
  RadioGroup text_wrap{{"None", "Character", "Word"}, [&](std::string s) {
                         entry.SetTextWrap(TextWraps.at(s));
                       }};
  text_wrap.SetSelectedRadio("Word");

  TextView vertical_alignment_label{"Vertical Alignment"};
  vertical_alignment_label.SetVerticalAlignment(Alignment::Center);
  vertical_alignment_label.SetTextAlignment(TextAlignment::Center);
  vertical_alignment_label.SetTextTruncation(TextTruncation::Ellipsis);
  vertical_alignment_label.SetTextWrap(TextWrap::None);
  TextView text_alignment_label{"Text Alignment"};
  text_alignment_label.SetVerticalAlignment(Alignment::Center);
  text_alignment_label.SetTextAlignment(TextAlignment::Center);
  text_alignment_label.SetTextTruncation(TextTruncation::Ellipsis);
  text_alignment_label.SetTextWrap(TextWrap::None);
  TextView text_truncation_label{"Text Truncation"};
  text_truncation_label.SetVerticalAlignment(Alignment::Center);
  text_truncation_label.SetTextAlignment(TextAlignment::Center);
  text_truncation_label.SetTextTruncation(TextTruncation::Ellipsis);
  text_truncation_label.SetTextWrap(TextWrap::None);
  TextView text_wrap_label{"Text Wrap"};
  text_wrap_label.SetVerticalAlignment(Alignment::Center);
  text_wrap_label.SetTextAlignment(TextAlignment::Center);
  text_wrap_label.SetTextTruncation(TextTruncation::Ellipsis);
  text_wrap_label.SetTextWrap(TextWrap::None);

  GridLayout grid{4, 6};
  grid.SetView(0, 0, &vertical_alignment_label, 1, 2);
  grid.SetView(0, 2, &vertical_alignment, 1, 3);
  grid.SetView(1, 0, &text_alignment_label, 1, 2);
  grid.SetView(1, 2, &text_alignment, 1, 4);
  grid.SetView(2, 0, &text_truncation_label, 1, 2);
  grid.SetView(2, 2, &text_truncation, 1, 3);
  grid.SetView(3, 0, &text_wrap_label, 1, 2);
  grid.SetView(3, 2, &text_wrap, 1, 3);

  EdgeLayout edge;
  edge.SetView(Location::Center, &entry);
  edge.SetView(Location::Bottom, &grid);

  window.SetContent(&edge);
  window.SetVisible(true);
  app.Start();
  return 0;
}
