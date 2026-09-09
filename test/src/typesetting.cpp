// Copyright 2026 Stuart Scott
#include <Pano/constants.h>
#include <Pano/font.h>
#include <Pano/typesetting.h>
#include <Pano/utf.h>
#include <PanoNotoSans/provider.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace Pano::Test {

// TODO Test Full Matrix;
// - Truncation
// - Wrapping
// - Text Alignment
// - Horizontal Alignment
// - Vertical Alignment

class TypesettingTest : public ::testing::Test {
 public:
  static void SetUpTestSuite() {
    ASSERT_TRUE(TTF_Init());
    TTF_Font* f = LoadNotoSansFont("NotoSans", TextStyle::Regular, 20);
    ASSERT_NE(f, nullptr);
    font_ = new Font(f);
  }

  static void TearDownTestSuite() {
    delete font_;
    font_ = nullptr;
    TTF_Quit();
  }

  static Font* font_;
};

Font* TypesettingTest::font_{nullptr};

constexpr int FontHeight{28};

constexpr float ViewWidth_Character_Small{10};
constexpr float ViewWidth_Character_Large{30};
constexpr float ViewHeight_Character_Small{20};
constexpr float ViewHeight_Character_Large{30};

constexpr float ViewWidth_Word_Small{50};
constexpr float ViewWidth_Word_Large{100};
constexpr float ViewHeight_Word_Small{20};
constexpr float ViewHeight_Word_2Lines{60};
constexpr float ViewHeight_Word_3Lines{90};

constexpr float ViewWidth_Sentence_Small{50};
constexpr float ViewWidth_Sentence_Large{440};
constexpr float ViewHeight_Sentence_Small{20};
constexpr float ViewHeight_Sentence_2Lines{60};
constexpr float ViewHeight_Sentence_3Lines{90};

constexpr char CharacterString[]{"M"};
constexpr char WordString[]{"Alphabets"};
constexpr char SentenceString[]{"The quick brown fox jumps over the lazy dog."};

const std::vector<std::string> WordLines_Truncated{"Alph", "abet", "s"};
const std::vector<std::string> WordLines_Truncated_Hyphenated{"Alp", "hab",
                                                              "ets"};
const std::vector<std::string> WordLines_Truncated_Ellipsis{"Alp"};
const std::vector<std::string> WordLines_Truncated_Ellipsis_Wrapped{"Alph",
                                                                    "abe"};
const std::vector<std::string> WordLines_Truncated_Ellipsis_Hyphenated{"Alp",
                                                                       "ha"};

const std::vector<std::string> SentenceLines_Truncated{"The ", "quic", "k bro"};
const std::vector<std::string> SentenceLines_Truncated_Hyphenated{"The ", "qui",
                                                                  "ck "};
const std::vector<std::string> SentenceLines_Truncated_Ellipsis{"The"};
const std::vector<std::string> SentenceLines_Truncated_Ellipsis_Wrapped{"The ",
                                                                        "qui"};
const std::vector<std::string> SentenceLines_Truncated_Ellipsis_Hyphenated{
    "The ", "qui", "ck"};

/*
…: 1 14 0 3 15
*/
constexpr float HorizontalEllipsisAdvance{15};

/*
-: 1 6 4 7 7
*/
constexpr float HyphenAdvance{7};

/*
M: 2 16 0 14 18
*/
const std::vector<float> CharacterXs{0, 18};
constexpr float CharacterWidth{18};

/*
A: 0 13 0 14 13
l: 2 4 0 15 6
p: 2 12 -5 11 13
h: 2 11 0 15 13
a: 1 10 0 11 11
b: 2 12 0 15 13
e: 1 10 0 11 11
t: 1 7 0 14 8
s: 1 9 0 11 10
*/
const std::vector<float> WordXs{0, 13, 19, 32, 45, 56, 69, 80, 88};
const std::vector<std::vector<float>> WordXs_Truncated{
    {0, 13, 19, 32, 45},
    {0, 11, 24, 35, 43},
    {0, 10},
};
const std::vector<std::vector<float>> WordXs_Truncated_Hyphenated{
    {0, 13, 19, 32, 32 + HyphenAdvance},
    {0, 13, 24, 37, 37 + HyphenAdvance},
    {0, 11, 19},
};
const std::vector<std::vector<float>> WordXs_Truncated_Ellipsis{
    {0, 13, 19, 32, 32 + HorizontalEllipsisAdvance},
};
const std::vector<std::vector<float>> WordXs_Truncated_Ellipsis_Wrapped{
    {0, 13, 19, 32},
    {0, 11, 24, 35, 35 + HorizontalEllipsisAdvance},
};
const std::vector<std::vector<float>> WordXs_Truncated_Ellipsis_Hyphenated{
    {0, 13, 19, 32, 32 + HyphenAdvance},
    {0, 13, 24, 24 + HorizontalEllipsisAdvance},
};

/*
T: 1 12 0 14 13
h: 2 11 0 15 13
e: 1 10 0 11 11
 : 0 0 0 0 5
q: 1 11 -5 11 13
u: 2 11 0 11 13
i: 2 4 0 15 6
c: 1 9 0 11 9
k: 2 11 0 15 11
 : 0 0 0 0 5
b: 2 12 0 15 13
r: 2 9 0 11 9
o: 1 11 0 11 12
w: 0 16 0 11 16
n: 2 11 0 11 13
 : 0 0 0 0 5
f: 1 9 0 15 8
o: 1 11 0 11 12
x: 0 11 0 11 11
 : 0 0 0 0 5
j: -1 4 -5 15 6
u: 2 11 0 11 13
m: 2 18 0 11 19
p: 2 12 -5 11 13
s: 1 9 0 11 10
 : 0 0 0 0 5
o: 1 11 0 11 12
v: 0 11 0 11 10
e: 1 10 0 11 11
r: 2 9 0 11 9
 : 0 0 0 0 5
t: 1 7 0 14 8
h: 2 11 0 15 13
e: 1 10 0 11 11
 : 0 0 0 0 5
l: 2 4 0 15 6
a: 1 10 0 11 11
z: 1 9 0 11 10
y: -1 10 -5 11 10
 : 0 0 0 0 5
d: 1 11 0 15 13
o: 1 11 0 11 12
g: 1 11 -5 11 13
.: 1 4 0 3 5
*/
const std::vector<float> SentenceXs{
    0,   13,  26,  37,  42,  55,  68,  74,  83,  94,  99,  112, 121, 133, 149,
    162, 167, 175, 187, 198, 203, 209, 222, 241, 254, 264, 269, 281, 291, 302,
    311, 316, 324, 337, 348, 353, 359, 370, 380, 390, 395, 408, 420, 433};
const std::vector<std::vector<float>> SentenceXs_Truncated{
    {0, 13, 26, 37},
    {0, 13, 26, 32},
    {0, 11, 16, 29, 38},
};
const std::vector<std::vector<float>> SentenceXs_Truncated_Hyphenated{
    {0, 13, 26},
    {0, 13, 26, 32, 32 + HyphenAdvance},
    {0, 9},
};
const std::vector<std::vector<float>> SentenceXs_Truncated_Ellipsis{
    {0, 13, 26, 37, 37 + HorizontalEllipsisAdvance},
};
const std::vector<std::vector<float>> SentenceXs_Truncated_Ellipsis_Wrapped{
    {0, 13, 26, 37},
    {0, 13, 26, 32, 32 + HorizontalEllipsisAdvance},
};
const std::vector<std::vector<float>> SentenceXs_Truncated_Ellipsis_Hyphenated{
    {0, 13, 26, 37},
    {0, 13, 26, 32, 32 + HyphenAdvance},
    {0, 9, 20, 20 + HorizontalEllipsisAdvance},
};

constexpr float WordWidth{98};
const std::vector<float> WordWidths_Truncated{45, 43, 10};
const std::vector<float> WordWidths_Truncated_Hyphenated{39, 44, 29};
const std::vector<float> WordWidths_Truncated_Ellipsis{47};
const std::vector<float> WordWidths_Truncated_Ellipsis_Wrapped{45, 50};
const std::vector<float> WordWidths_Truncated_Ellipsis_Hyphenated{39, 39};

constexpr float SentenceWidth{438};
const std::vector<float> SentenceWidths_Truncated{42, 41, 50};
const std::vector<float> SentenceWidths_Truncated_Hyphenated{42, 39, 25};
const std::vector<float> SentenceWidths_Truncated_Ellipsis{52};
const std::vector<float> SentenceWidths_Truncated_Ellipsis_Wrapped{42, 47};
const std::vector<float> SentenceWidths_Truncated_Ellipsis_Hyphenated{42, 39,
                                                                      35};

TEST_F(TypesettingTest, Empty) {
  std::vector<UTFGlyph*> gs;
  for (const auto t :
       {TextTruncation::None, TextTruncation::Clip, TextTruncation::Ellipsis}) {
    for (const auto w : {TextWrap::None, TextWrap::Character, TextWrap::Word}) {
      Typesetter typesetter(
          TypesettingTest::font_, gs, Alignment::Start, TextAlignment::Start, t,
          w, ViewWidth_Character_Large, ViewHeight_Character_Large);
      typesetter.Typeset();
      const auto lines = typesetter.GetLines();
      ASSERT_EQ(0, lines.size());
    }
  }
}

TEST_F(TypesettingTest, Character_TruncationNone_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::None,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::None,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::None,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Character_TruncationNone_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::Character,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::Character,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::Character,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Character_TruncationNone_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::Word,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::Word,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::None, TextWrap::Word,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Character_TruncationClip_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::None,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::None,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::None,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Character_TruncationClip_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::Character,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::Character,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::Character,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Character_TruncationClip_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::Word,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::Word,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Clip, TextWrap::Word,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Character_TruncationEllipsis_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::None,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::None,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::None,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Character_TruncationEllipsis_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::Character,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::Character,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::Character,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Character_TruncationEllipsis_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::Word,
        ViewWidth_Character_Large, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(CharacterString, text);
    const auto char_position = line->GetPosition(0);
    ASSERT_EQ(0, char_position.x);
    ASSERT_EQ(0, char_position.y);
    const auto size = line->GetSize();
    ASSERT_EQ(CharacterWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::Word,
        ViewWidth_Character_Small, ViewHeight_Character_Large);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }

  {
    // View is too short
    Typesetter typesetter(
        TypesettingTest::font_, SplitUTF8(CharacterString), Alignment::Start,
        TextAlignment::Start, TextTruncation::Ellipsis, TextWrap::Word,
        ViewWidth_Character_Large, ViewHeight_Character_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationNone_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::None,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::None,
                          ViewWidth_Word_Small, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_FALSE(line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(WordLines_Truncated[i], text);
      for (size_t j = 0; j < WordXs_Truncated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(WordXs_Truncated[i][j], char_position.x);
        ASSERT_EQ(0, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(WordWidths_Truncated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::None,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationNone_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Character,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Character,
                          ViewWidth_Word_Small, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(3, lines.size());
    for (size_t i = 0; i < WordLines_Truncated.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_FALSE(line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(WordLines_Truncated[i], text);
      for (size_t j = 0; j < WordXs_Truncated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(WordXs_Truncated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(WordWidths_Truncated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Character,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationNone_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Word,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Word,
                          ViewWidth_Word_Small, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(3, lines.size());
    for (size_t i = 0; i < WordLines_Truncated_Hyphenated.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_EQ(i < 2, line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(WordLines_Truncated_Hyphenated[i], text);
      for (size_t j = 0; j < WordXs_Truncated_Hyphenated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(WordXs_Truncated_Hyphenated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(WordWidths_Truncated_Hyphenated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Word,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationClip_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::None,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::None,
                          ViewWidth_Word_Small, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordLines_Truncated[0], text);
    for (size_t j = 0; j < WordXs_Truncated[0].size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs_Truncated[0][j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidths_Truncated[0], size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::None,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationClip_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Character,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Character,
                          ViewWidth_Word_Small, ViewHeight_Word_2Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(2, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_FALSE(line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(WordLines_Truncated[i], text);
      for (size_t j = 0; j < WordXs_Truncated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(WordXs_Truncated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(WordWidths_Truncated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Character,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationClip_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Word,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Word,
                          ViewWidth_Word_Small, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(3, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_EQ(i < 2, line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(WordLines_Truncated_Hyphenated[i], text);
      for (size_t j = 0; j < WordXs_Truncated_Hyphenated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(WordXs_Truncated_Hyphenated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(WordWidths_Truncated_Hyphenated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Word,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationEllipsis_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::None,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::None,
                          ViewWidth_Word_Small, ViewHeight_Word_2Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_TRUE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordLines_Truncated_Ellipsis[0], text);
    for (size_t j = 0; j < WordXs_Truncated_Ellipsis[0].size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs_Truncated_Ellipsis[0][j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidths_Truncated_Ellipsis[0], size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::None,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationEllipsis_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Character,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Character,
                          ViewWidth_Word_Small, ViewHeight_Word_2Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(2, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_EQ(i > 0, line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_FALSE(line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(WordLines_Truncated_Ellipsis_Wrapped[i], text);
      for (size_t j = 0; j < WordXs_Truncated_Ellipsis_Wrapped[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(WordXs_Truncated_Ellipsis_Wrapped[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(WordWidths_Truncated_Ellipsis_Wrapped[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Character,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Word_TruncationEllipsis_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Word,
                          ViewWidth_Word_Large, ViewHeight_Word_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(WordString, text);
    for (size_t j = 0; j < WordXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(WordXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(WordWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Word,
                          ViewWidth_Word_Small, ViewHeight_Word_2Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(2, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_EQ(i > 0, line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_EQ(i == 0, line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(WordLines_Truncated_Ellipsis_Hyphenated[i], text);
      for (size_t j = 0; j < WordXs_Truncated_Ellipsis_Hyphenated[i].size();
           ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(WordXs_Truncated_Ellipsis_Hyphenated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(WordWidths_Truncated_Ellipsis_Hyphenated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(WordString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Word,
                          ViewWidth_Word_Large, ViewHeight_Word_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationNone_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::None,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::None,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_FALSE(line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(SentenceLines_Truncated[i], text);
      for (size_t j = 0; j < SentenceXs_Truncated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(SentenceXs_Truncated[i][j], char_position.x);
        ASSERT_EQ(0, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(SentenceWidths_Truncated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::None,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationNone_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Character,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Character,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(3, lines.size());
    for (size_t i = 0; i < SentenceLines_Truncated.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_FALSE(line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(SentenceLines_Truncated[i], text);
      for (size_t j = 0; j < SentenceXs_Truncated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(SentenceXs_Truncated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(SentenceWidths_Truncated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Character,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationNone_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Word,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Word,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(3, lines.size());
    for (size_t i = 0; i < SentenceLines_Truncated_Hyphenated.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_EQ(i == 1, line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(SentenceLines_Truncated_Hyphenated[i], text);
      for (size_t j = 0; j < SentenceXs_Truncated_Hyphenated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(SentenceXs_Truncated_Hyphenated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(SentenceWidths_Truncated_Hyphenated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::None, TextWrap::Word,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationClip_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::None,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::None,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceLines_Truncated[0], text);
    for (size_t j = 0; j < SentenceXs_Truncated[0].size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs_Truncated[0][j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidths_Truncated[0], size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::None,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationClip_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Character,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Character,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_2Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(2, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_FALSE(line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(SentenceLines_Truncated[i], text);
      for (size_t j = 0; j < SentenceXs_Truncated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(SentenceXs_Truncated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(SentenceWidths_Truncated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Character,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationClip_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Word,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Word,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(3, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_FALSE(line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_EQ(i == 1, line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(SentenceLines_Truncated_Hyphenated[i], text);
      for (size_t j = 0; j < SentenceXs_Truncated_Hyphenated[i].size(); ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(SentenceXs_Truncated_Hyphenated[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(SentenceWidths_Truncated_Hyphenated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Clip, TextWrap::Word,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationEllipsis_WrappingNone) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::None,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::None,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_2Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_TRUE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceLines_Truncated_Ellipsis[0], text);
    for (size_t j = 0; j < SentenceXs_Truncated_Ellipsis[0].size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs_Truncated_Ellipsis[0][j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidths_Truncated_Ellipsis[0], size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::None,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationEllipsis_WrappingCharacter) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Character,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Character,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_2Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(2, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_EQ(i > 0, line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_FALSE(line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(SentenceLines_Truncated_Ellipsis_Wrapped[i], text);
      for (size_t j = 0; j < SentenceXs_Truncated_Ellipsis_Wrapped[i].size();
           ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(SentenceXs_Truncated_Ellipsis_Wrapped[i][j], char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(SentenceWidths_Truncated_Ellipsis_Wrapped[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Character,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

TEST_F(TypesettingTest, Sentence_TruncationEllipsis_WrappingWord) {
  {
    // View is big enough
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Word,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(1, lines.size());
    const auto line = lines[0];
    ASSERT_FALSE(line->HasHorizontalEllipsis());
    ASSERT_FALSE(line->HasVerticalEllipsis());
    ASSERT_FALSE(line->HasHyphen());
    const auto text = line->GetText();
    ASSERT_EQ(SentenceString, text);
    for (size_t j = 0; j < SentenceXs.size(); ++j) {
      const auto char_position = line->GetPosition(j);
      ASSERT_EQ(SentenceXs[j], char_position.x);
      ASSERT_EQ(0, char_position.y);
    }
    const auto size = line->GetSize();
    ASSERT_EQ(SentenceWidth, size.width);
    ASSERT_EQ(FontHeight, size.height);
  }

  {
    // View is too narrow
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Word,
                          ViewWidth_Sentence_Small, ViewHeight_Sentence_3Lines);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(3, lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
      const auto line = lines[i];
      ASSERT_EQ(i == 2, line->HasHorizontalEllipsis());
      ASSERT_FALSE(line->HasVerticalEllipsis());
      ASSERT_EQ(i == 1, line->HasHyphen());
      const auto text = line->GetText();
      ASSERT_EQ(SentenceLines_Truncated_Ellipsis_Hyphenated[i], text);
      for (size_t j = 0; j < SentenceXs_Truncated_Ellipsis_Hyphenated[i].size();
           ++j) {
        const auto char_position = line->GetPosition(j);
        ASSERT_EQ(SentenceXs_Truncated_Ellipsis_Hyphenated[i][j],
                  char_position.x);
        ASSERT_EQ(i * FontHeight, char_position.y);
      }
      const auto size = line->GetSize();
      ASSERT_EQ(SentenceWidths_Truncated_Ellipsis_Hyphenated[i], size.width);
      ASSERT_EQ(FontHeight, size.height);
    }
  }

  {
    // View is too short
    Typesetter typesetter(TypesettingTest::font_, SplitUTF8(SentenceString),
                          Alignment::Start, TextAlignment::Start,
                          TextTruncation::Ellipsis, TextWrap::Word,
                          ViewWidth_Sentence_Large, ViewHeight_Sentence_Small);
    typesetter.Typeset();

    const auto lines = typesetter.GetLines();
    ASSERT_EQ(0, lines.size());
  }
}

/*
constexpr char ParagraphString[]{
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod "
    "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "
    "veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
    "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "
    "velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "
    "occaecat cupidatat non proident, sunt in culpa qui officia deserunt "
    "mollit anim id est laborum."};
TEST_F(TypesettingTest, Paragraph_TruncationNone_WrappingNone) {
TEST_F(TypesettingTest, Paragraph_TruncationNone_WrappingCharacter) {
TEST_F(TypesettingTest, Paragraph_TruncationNone_WrappingWord) {
TEST_F(TypesettingTest, Paragraph_TruncationClip_WrappingNone) {
TEST_F(TypesettingTest, Paragraph_TruncationClip_WrappingCharacter) {
TEST_F(TypesettingTest, Paragraph_TruncationClip_WrappingWord) {
TEST_F(TypesettingTest, Paragraph_TruncationEllipsis_WrappingNone) {
TEST_F(TypesettingTest, Paragraph_TruncationEllipsis_WrappingCharacter) {
TEST_F(TypesettingTest, Paragraph_TruncationEllipsis_WrappingWord) {
*/
};  // namespace Pano::Test
