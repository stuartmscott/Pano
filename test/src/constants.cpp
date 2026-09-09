// Copyright 2026 Stuart Scott
#include <Pano/constants.h>
#include <gtest/gtest.h>

#include <string>

namespace Pano::Test {

TEST(ConstantsTest, Alignment_ToString) {
  ASSERT_EQ("Start", ToString(Alignment::Start));
  ASSERT_EQ("Center", ToString(Alignment::Center));
  ASSERT_EQ("End", ToString(Alignment::End));
}

TEST(ConstantsTest, Axis_ToString) {
  ASSERT_EQ("X", ToString(Axis::X));
  ASSERT_EQ("Y", ToString(Axis::Y));
  ASSERT_EQ("Z", ToString(Axis::Z));
}

TEST(ConstantsTest, Condition_Not) {
  ASSERT_EQ(255, static_cast<uint8_t>(~Condition::Disabled));
  ASSERT_EQ(254, static_cast<uint8_t>(~Condition::Enabled));
  ASSERT_EQ(253, static_cast<uint8_t>(~Condition::Focused));
  ASSERT_EQ(251, static_cast<uint8_t>(~Condition::Activated));
}

TEST(ConstantsTest, Condition_And) {
  ASSERT_EQ(Condition::Enabled, Condition::Enabled & Condition::Enabled);
  uint8_t max{255};
  ASSERT_EQ(Condition::Activated,
            static_cast<Condition>(max) & Condition::Activated);
}

TEST(ConstantsTest, Condition_Or) {
  ASSERT_EQ(static_cast<Condition>(5),
            Condition::Enabled | Condition::Activated);
  uint8_t zero{0};
  ASSERT_EQ(Condition::Activated,
            static_cast<Condition>(zero) | Condition::Activated);
}

TEST(ConstantsTest, Condition_IsBitSet) {
  uint8_t zero{0};
  ASSERT_FALSE(IsBitSet(static_cast<Condition>(zero), Condition::Enabled));
  ASSERT_FALSE(IsBitSet(static_cast<Condition>(zero), Condition::Focused));
  ASSERT_FALSE(IsBitSet(static_cast<Condition>(zero), Condition::Activated));
  uint8_t max{255};
  ASSERT_TRUE(IsBitSet(static_cast<Condition>(max), Condition::Enabled));
  ASSERT_TRUE(IsBitSet(static_cast<Condition>(max), Condition::Focused));
  ASSERT_TRUE(IsBitSet(static_cast<Condition>(max), Condition::Activated));
}

TEST(ConstantsTest, Condition_SetBit) {
  uint8_t zero{0};
  ASSERT_EQ(Condition::Enabled,
            SetBit(static_cast<Condition>(zero), Condition::Enabled));
  ASSERT_EQ(Condition::Focused,
            SetBit(static_cast<Condition>(zero), Condition::Focused));
  ASSERT_EQ(Condition::Activated,
            SetBit(static_cast<Condition>(zero), Condition::Activated));
}

TEST(ConstantsTest, Condition_ClearBit) {
  ASSERT_EQ(Condition::Disabled,
            ClearBit(Condition::Enabled, Condition::Enabled));
  ASSERT_EQ(Condition::Disabled,
            ClearBit(Condition::Focused, Condition::Focused));
  ASSERT_EQ(Condition::Disabled,
            ClearBit(Condition::Activated, Condition::Activated));
  ASSERT_EQ(Condition::Disabled,
            ClearBit(Condition::Focused | Condition::Activated,
                     Condition::Focused | Condition::Activated));
}

TEST(ConstantsTest, Condition_ToString) {
  ASSERT_EQ("Disabled", ToString(Condition::Disabled));
  ASSERT_EQ("DisabledFocused", ToString(Condition::Focused));
  ASSERT_EQ("DisabledActivated", ToString(Condition::Activated));
  ASSERT_EQ("DisabledFocusedActivated",
            ToString(Condition::Focused | Condition::Activated));
  ASSERT_EQ("Enabled", ToString(Condition::Enabled));
  ASSERT_EQ("EnabledFocused",
            ToString(Condition::Enabled | Condition::Focused));
  ASSERT_EQ("EnabledActivated",
            ToString(Condition::Enabled | Condition::Activated));
  ASSERT_EQ(
      "EnabledFocusedActivated",
      ToString(Condition::Enabled | Condition::Focused | Condition::Activated));
}

TEST(ConstantsTest, Layer_ToString) {
  ASSERT_EQ("Background", ToString(Layer::Background));
  ASSERT_EQ("Foreground", ToString(Layer::Foreground));
}

TEST(ConstantsTest, Location_ToString) {
  ASSERT_EQ("Top", ToString(Location::Top));
  ASSERT_EQ("Bottom", ToString(Location::Bottom));
  ASSERT_EQ("Left", ToString(Location::Left));
  ASSERT_EQ("Right", ToString(Location::Right));
  ASSERT_EQ("Center", ToString(Location::Center));
}

TEST(ConstantsTest, Significance_ToString) {
  ASSERT_EQ("Normal", ToString(Significance::Normal));
  ASSERT_EQ("Primary", ToString(Significance::Primary));
  ASSERT_EQ("Secondary", ToString(Significance::Secondary));
  ASSERT_EQ("TextTitle", ToString(Significance::TextTitle));
  ASSERT_EQ("TextHeading1", ToString(Significance::TextHeading1));
  ASSERT_EQ("TextHeading2", ToString(Significance::TextHeading2));
  ASSERT_EQ("TextHeading3", ToString(Significance::TextHeading3));
  ASSERT_EQ("TextHeading4", ToString(Significance::TextHeading4));
  ASSERT_EQ("TextHeading5", ToString(Significance::TextHeading5));
  ASSERT_EQ("TextHeading6", ToString(Significance::TextHeading6));
  ASSERT_EQ("TextSubtitle", ToString(Significance::TextSubtitle));
  ASSERT_EQ("TextBody", ToString(Significance::TextBody));
  ASSERT_EQ("TextCaption", ToString(Significance::TextCaption));
  ASSERT_EQ("Information", ToString(Significance::Information));
  ASSERT_EQ("Warning", ToString(Significance::Warning));
  ASSERT_EQ("Error", ToString(Significance::Error));
  ASSERT_EQ("Danger", ToString(Significance::Danger));
}

TEST(ConstantsTest, TextAlignment_ToString) {
  ASSERT_EQ("Start", ToString(TextAlignment::Start));
  ASSERT_EQ("Center", ToString(TextAlignment::Center));
  ASSERT_EQ("End", ToString(TextAlignment::End));
  ASSERT_EQ("Justify", ToString(TextAlignment::Justify));
}

TEST(ConstantsTest, TextTruncation_ToString) {
  ASSERT_EQ("None", ToString(TextTruncation::None));
  ASSERT_EQ("Clip", ToString(TextTruncation::Clip));
  ASSERT_EQ("Ellipsis", ToString(TextTruncation::Ellipsis));
}

TEST(ConstantsTest, TextWrap_ToString) {
  ASSERT_EQ("None", ToString(TextWrap::None));
  ASSERT_EQ("Character", ToString(TextWrap::Character));
  ASSERT_EQ("Word", ToString(TextWrap::Word));
}

TEST(ConstantsTest, TextStyle_And) {
  ASSERT_EQ(TextStyle::Bold, TextStyle::Bold & TextStyle::Bold);
  uint8_t max{255};
  ASSERT_EQ(TextStyle::Bold, static_cast<TextStyle>(max) & TextStyle::Bold);
}

TEST(ConstantsTest, TextStyle_Or) {
  ASSERT_EQ(TextStyle::BoldItalic, TextStyle::Bold | TextStyle::Italic);
  uint8_t zero{0};
  ASSERT_EQ(TextStyle::Monospace,
            static_cast<TextStyle>(zero) | TextStyle::Monospace);
}

TEST(ConstantsTest, TextStyle_ToString) {
  ASSERT_EQ("Regular", ToString(TextStyle::Regular));
  ASSERT_EQ("Bold", ToString(TextStyle::Bold));
  ASSERT_EQ("Italic", ToString(TextStyle::Italic));
  ASSERT_EQ("BoldItalic", ToString(TextStyle::BoldItalic));
  ASSERT_EQ("BoldItalic", ToString(TextStyle::Bold | TextStyle::Italic));
  ASSERT_EQ("Monospace", ToString(TextStyle::Monospace));
}
};  // namespace Pano::Test
