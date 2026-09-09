// Copyright 2026 Stuart Scott
#include <Pano/utf.h>
#include <gtest/gtest.h>

#include <string>

namespace Pano::Test {

constexpr char32_t UTF_Char_1Byte{U'A'};
constexpr char32_t UTF_Char_2Byte{U'£'};
constexpr char32_t UTF_Char_3Byte{U'অ'};
constexpr char32_t UTF_Char_4Byte{U'𐌀'};

constexpr std::string UTF_String{"ABC"};
constexpr std::string UTF_String_0{"A"};
constexpr std::string UTF_String_1{"B"};
constexpr std::string UTF_String_2{"C"};

constexpr std::string UTF_String_Modified{"A\u200CB\u200CC\u200C"};
constexpr std::string UTF_String_0_Modified{"A\u200C"};
constexpr std::string UTF_String_1_Modified{"B\u200C"};
constexpr std::string UTF_String_2_Modified{"C\u200C"};

constexpr std::string UTF_String_1Byte{"A"};
constexpr std::string UTF_String_2Byte{"£"};
constexpr std::string UTF_String_3Byte{"অ"};
constexpr std::string UTF_String_4Byte{"𐌀"};

constexpr std::string UTF_String_1Byte_Modified{"A\u200C"};
constexpr std::string UTF_String_2Byte_Modified{"£\u200C"};
constexpr std::string UTF_String_3Byte_Modified{"অ\u200C"};
constexpr std::string UTF_String_4Byte_Modified{"𐌀\u200C"};

constexpr std::u8string UTF8_1Byte{u8"A"};
constexpr std::u8string UTF8_2Byte{u8"£"};
constexpr std::u8string UTF8_3Byte{u8"অ"};
constexpr std::u8string UTF8_4Byte{u8"𐌀"};

constexpr std::u32string UTF32_1Byte{U"A"};
constexpr std::u32string UTF32_2Byte{U"£"};
constexpr std::u32string UTF32_3Byte{U"অ"};
constexpr std::u32string UTF32_4Byte{U"𐌀"};

TEST(UTFTest, From_1Byte) {
  std::u32string out;
  UTF8To32(UTF8_1Byte, out);
  ASSERT_EQ(UTF32_1Byte, out);
}

TEST(UTFTest, From_2Byte) {
  std::u32string out;
  UTF8To32(UTF8_2Byte, out);
  ASSERT_EQ(UTF32_2Byte, out);
}

TEST(UTFTest, From_3Byte) {
  std::u32string out;
  UTF8To32(UTF8_3Byte, out);
  ASSERT_EQ(UTF32_3Byte, out);
}

TEST(UTFTest, From_4Byte) {
  std::u32string out;
  UTF8To32(UTF8_4Byte, out);
  ASSERT_EQ(UTF32_4Byte, out);
}

TEST(UTFTest, To_1Byte) {
  std::u8string out;
  UTF32To8(UTF32_1Byte, out);
  ASSERT_EQ(UTF8_1Byte, out);
}

TEST(UTFTest, To_2Byte) {
  std::u8string out;
  UTF32To8(UTF32_2Byte, out);
  ASSERT_EQ(UTF8_2Byte, out);
}

TEST(UTFTest, To_3Byte) {
  std::u8string out;
  UTF32To8(UTF32_3Byte, out);
  ASSERT_EQ(UTF8_3Byte, out);
}

TEST(UTFTest, To_4Byte) {
  std::u8string out;
  UTF32To8(UTF32_4Byte, out);
  ASSERT_EQ(UTF8_4Byte, out);
}

// http://www.cl.cam.ac.uk/~mgk25/ucs/examples/quickbrown.txt

TEST(UTFTest, Danish) {
  std::u8string UTF8_Danish =
      u8"Quizdeltagerne spiste jordbær med fløde, mens cirkusklovnen Wolther "
      u8"spillede på xylofon.";
  std::u32string UTF32_Danish =
      U"Quizdeltagerne spiste jordbær med fløde, mens cirkusklovnen Wolther "
      U"spillede på xylofon.";
  {
    std::u32string out;
    UTF8To32(UTF8_Danish, out);
    ASSERT_EQ(UTF32_Danish, out);
  }
  {
    std::u8string out;
    UTF32To8(UTF32_Danish, out);
    ASSERT_EQ(UTF8_Danish, out);
  }
}

TEST(UTFTest, German) {
  std::u8string UTF8_German =
      u8"Zwölf Boxkämpfer jagten Eva quer über den Sylter Deich";
  std::u32string UTF32_German =
      U"Zwölf Boxkämpfer jagten Eva quer über den Sylter Deich";
  {
    std::u32string out;
    UTF8To32(UTF8_German, out);
    ASSERT_EQ(UTF32_German, out);
  }
  {
    std::u8string out;
    UTF32To8(UTF32_German, out);
    ASSERT_EQ(UTF8_German, out);
  }
}

TEST(UTFTest, Katakana) {
  std::u8string UTF8_Katakana =
      u8"イロハニホヘト チリヌルヲ ワカヨタレソ ツネナラム ウヰノオクヤマ "
      u8"ケフコエテ アサキユメミシ ヱヒモセスン";
  std::u32string UTF32_Katakana =
      U"イロハニホヘト チリヌルヲ ワカヨタレソ ツネナラム ウヰノオクヤマ "
      U"ケフコエテ アサキユメミシ ヱヒモセスン";
  {
    std::u32string out;
    UTF8To32(UTF8_Katakana, out);
    ASSERT_EQ(UTF32_Katakana, out);
  }
  {
    std::u8string out;
    UTF32To8(UTF32_Katakana, out);
    ASSERT_EQ(UTF8_Katakana, out);
  }
}

TEST(UTFTest, IsUTFModifier) {
  // Spacing Modifier Letters
  ASSERT_TRUE(IsUTFModifier(U'\U000002B0'));
  ASSERT_TRUE(IsUTFModifier(U'\U000002D8'));
  ASSERT_TRUE(IsUTFModifier(U'\U000002FF'));
  // Nonspacing Marks (Diacritical Marks)
  ASSERT_TRUE(IsUTFModifier(U'\U00000300'));
  ASSERT_TRUE(IsUTFModifier(U'\U00000338'));
  ASSERT_TRUE(IsUTFModifier(U'\U0000036F'));
  // Mongolian Variant Selectors
  ASSERT_TRUE(IsUTFModifier(U'\U0000180B'));
  ASSERT_TRUE(IsUTFModifier(U'\U0000180D'));
  ASSERT_TRUE(IsUTFModifier(U'\U0000180F'));
  // Joining
  ASSERT_TRUE(IsUTFModifier(U'\U0000200C'));
  ASSERT_TRUE(IsUTFModifier(U'\U0000200D'));
  // Variant Selector
  ASSERT_TRUE(IsUTFModifier(U'\U0000FE00'));
  ASSERT_TRUE(IsUTFModifier(U'\U0000FE0D'));
  ASSERT_TRUE(IsUTFModifier(U'\U0000FE0F'));
  // Emoji Modifier
  ASSERT_TRUE(IsUTFModifier(U'\U0001F3FB'));
  ASSERT_TRUE(IsUTFModifier(U'\U0001F3FD'));
  ASSERT_TRUE(IsUTFModifier(U'\U0001F3FF'));
  // Variant Selector Supplement
  ASSERT_TRUE(IsUTFModifier(U'\U000E0100'));
  ASSERT_TRUE(IsUTFModifier(U'\U000E0100'));
  ASSERT_TRUE(IsUTFModifier(U'\U000E0177'));
  // Non-Modifier
  ASSERT_FALSE(IsUTFModifier(U'0'));
  ASSERT_FALSE(IsUTFModifier(U'A'));
  ASSERT_FALSE(IsUTFModifier(U'a'));
  ASSERT_FALSE(IsUTFModifier(U'`'));
}

TEST(UTFTest, NextUTFCodepoint_1Byte) {
  auto it = UTF_String_1Byte.cbegin();
  const auto end = UTF_String_1Byte.cend();
  const auto c = NextUTFCodepoint(it, end);
  ASSERT_EQ(UTF_Char_1Byte, c);
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFCodepoint_2Byte) {
  auto it = UTF_String_2Byte.cbegin();
  const auto end = UTF_String_2Byte.cend();
  const auto c = NextUTFCodepoint(it, end);
  ASSERT_EQ(UTF_Char_2Byte, c);
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFCodepoint_3Byte) {
  auto it = UTF_String_3Byte.cbegin();
  const auto end = UTF_String_3Byte.cend();
  const auto c = NextUTFCodepoint(it, end);
  ASSERT_EQ(UTF_Char_3Byte, c);
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFCodepoint_4Byte) {
  auto it = UTF_String_4Byte.cbegin();
  const auto end = UTF_String_4Byte.cend();
  const auto c = NextUTFCodepoint(it, end);
  ASSERT_EQ(UTF_Char_4Byte, c);
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_1Byte) {
  auto it = UTF_String_1Byte.cbegin();
  const auto end = UTF_String_1Byte.cend();
  const auto g = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_1Byte, g->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_2Byte) {
  auto it = UTF_String_2Byte.cbegin();
  const auto end = UTF_String_2Byte.cend();
  const auto g = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_2Byte, g->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_3Byte) {
  auto it = UTF_String_3Byte.cbegin();
  const auto end = UTF_String_3Byte.cend();
  const auto g = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_3Byte, g->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_4Byte) {
  auto it = UTF_String_4Byte.cbegin();
  const auto end = UTF_String_4Byte.cend();
  const auto g = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_4Byte, g->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_1Byte_Modified) {
  auto it = UTF_String_1Byte_Modified.cbegin();
  const auto end = UTF_String_1Byte_Modified.cend();
  const auto g = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_1Byte_Modified, g->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_2Byte_Modified) {
  auto it = UTF_String_2Byte_Modified.cbegin();
  const auto end = UTF_String_2Byte_Modified.cend();
  const auto g = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_2Byte_Modified, g->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_3Byte_Modified) {
  auto it = UTF_String_3Byte_Modified.cbegin();
  const auto end = UTF_String_3Byte_Modified.cend();
  const auto g = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_3Byte_Modified, g->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_4Byte_Modified) {
  auto it = UTF_String_4Byte_Modified.cbegin();
  const auto end = UTF_String_4Byte_Modified.cend();
  const auto g = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_4Byte_Modified, g->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_String) {
  auto it = UTF_String.cbegin();
  const auto end = UTF_String.cend();
  const auto g0 = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_0, g0->GetText());
  ASSERT_NE(it, end);
  const auto g1 = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_1, g1->GetText());
  ASSERT_NE(it, end);
  const auto g2 = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_2, g2->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, NextUTFGlyph_String_Modified) {
  auto it = UTF_String_Modified.cbegin();
  const auto end = UTF_String_Modified.cend();
  const auto g0 = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_0_Modified, g0->GetText());
  ASSERT_NE(it, end);
  const auto g1 = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_1_Modified, g1->GetText());
  ASSERT_NE(it, end);
  const auto g2 = NextUTFGlyph(it, end);
  ASSERT_EQ(UTF_String_2_Modified, g2->GetText());
  ASSERT_EQ(it, end);
}

TEST(UTFTest, SplitUTF8) {
  const auto gs = SplitUTF8(UTF_String);
  ASSERT_EQ(3, gs.size());
  ASSERT_EQ(UTF_String_0, gs[0]->GetText());
  ASSERT_EQ(UTF_String_1, gs[1]->GetText());
  ASSERT_EQ(UTF_String_2, gs[2]->GetText());
}

TEST(UTFTest, SplitUTF8_Modified) {
  const auto gs = SplitUTF8(UTF_String_Modified);
  ASSERT_EQ(3, gs.size());
  ASSERT_EQ(UTF_String_0_Modified, gs[0]->GetText());
  ASSERT_EQ(UTF_String_1_Modified, gs[1]->GetText());
  ASSERT_EQ(UTF_String_2_Modified, gs[2]->GetText());
}
};  // namespace Pano::Test
