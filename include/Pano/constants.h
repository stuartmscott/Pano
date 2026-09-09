// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_CONSTANTS_H_
#define INCLUDE_PANO_CONSTANTS_H_

#include <cstdint>
#include <string>

namespace Pano {
constexpr uint32_t WindowWidth{800};
constexpr uint32_t WindowHeight{600};

constexpr char32_t HorizontalEllipsisChar{U'…'};
constexpr char32_t VerticalEllipsisChar{U'⋮'};
constexpr char32_t HyphenChar{U'‐'};
constexpr char32_t NewLineChar{U'\n'};
constexpr char32_t SpaceChar{U' '};

constexpr std::string HorizontalEllipsisString{"…"};
constexpr std::string VerticalEllipsisString{"⋮"};
constexpr std::string HyphenString{"‐"};

enum class Alignment { Start, Center, End };

constexpr std::string ToString(const Alignment a) {
  switch (a) {
    case Alignment::Start:
      return "Start";
    case Alignment::Center:
      return "Center";
    case Alignment::End:
      return "End";
  }
  return "Unrecognized Alignment";
}

enum class Axis {
  X,
  Y,
  Z,
};

constexpr std::string ToString(const Axis a) {
  switch (a) {
    case Axis::X:
      return "X";
    case Axis::Y:
      return "Y";
    case Axis::Z:
      return "Z";
  }
  return "Unrecognized Axis";
}

enum class Condition : uint8_t {
  Disabled = 0,
  Enabled = 1 << 0,
  Focused = 1 << 1,
  Activated = 1 << 2,
};

constexpr Condition operator~(Condition c) {
  return static_cast<Condition>(~static_cast<uint8_t>(c));
}

constexpr Condition operator&(Condition a, Condition b) {
  return static_cast<Condition>(static_cast<uint8_t>(a) &
                                static_cast<uint8_t>(b));
}

constexpr Condition operator|(Condition a, Condition b) {
  return static_cast<Condition>(static_cast<uint8_t>(a) |
                                static_cast<uint8_t>(b));
}

constexpr bool IsBitSet(Condition a, Condition b) { return (a & b) == b; }

constexpr Condition SetBit(Condition a, Condition b) { return (a | b); }

constexpr Condition ClearBit(Condition a, Condition b) { return (a & ~b); }

constexpr std::string ToString(const Condition c) {
  std::string result{IsBitSet(c, Condition::Enabled) ? "Enabled" : "Disabled"};
  if (IsBitSet(c, Condition::Focused)) {
    result += "Focused";
  }
  if (IsBitSet(c, Condition::Activated)) {
    result += "Activated";
  }
  return result;
}

enum class Icon {
  None,
  ArrowDropDown,
  CheckBoxChecked,
  CheckBoxUnchecked,
  Pano,
  RadioButtonSelected,
  RadioButtonUnselected
};

constexpr std::string ToString(const Icon i) {
  switch (i) {
    case Icon::None:
      return "None";
    case Icon::ArrowDropDown:
      return "ArrowDropDown";
    case Icon::CheckBoxChecked:
      return "CheckBoxChecked";
    case Icon::CheckBoxUnchecked:
      return "CheckBoxUnchecked";
    case Icon::Pano:
      return "Pano";
    case Icon::RadioButtonSelected:
      return "RadioButtonSelected";
    case Icon::RadioButtonUnselected:
      return "RadioButtonUnselected";
  }
  return "Unrecognized Icon";
}

enum class Layer { Background, Foreground };

constexpr std::string ToString(const Layer l) {
  switch (l) {
    case Layer::Background:
      return "Background";
    case Layer::Foreground:
      return "Foreground";
  }
  return "Unrecognized Layer";
}

enum class Location {
  Center,
  Top,
  Bottom,
  Left,
  Right,
};

constexpr std::string ToString(const Location l) {
  switch (l) {
    case Location::Center:
      return "Center";
    case Location::Top:
      return "Top";
    case Location::Bottom:
      return "Bottom";
    case Location::Left:
      return "Left";
    case Location::Right:
      return "Right";
  }
  return "Unrecognized Location";
}

enum class Significance {
  Normal,
  Primary,
  Secondary,
  TextTitle,
  TextHeading1,
  TextHeading2,
  TextHeading3,
  TextHeading4,
  TextHeading5,
  TextHeading6,
  TextSubtitle,
  TextBody,
  TextCaption,
  Information,
  Warning,
  Error,
  Danger
};

constexpr std::string ToString(const Significance s) {
  switch (s) {
    case Significance::Normal:
      return "Normal";
    case Significance::Primary:
      return "Primary";
    case Significance::Secondary:
      return "Secondary";
    case Significance::TextTitle:
      return "TextTitle";
    case Significance::TextHeading1:
      return "TextHeading1";
    case Significance::TextHeading2:
      return "TextHeading2";
    case Significance::TextHeading3:
      return "TextHeading3";
    case Significance::TextHeading4:
      return "TextHeading4";
    case Significance::TextHeading5:
      return "TextHeading5";
    case Significance::TextHeading6:
      return "TextHeading6";
    case Significance::TextSubtitle:
      return "TextSubtitle";
    case Significance::TextBody:
      return "TextBody";
    case Significance::TextCaption:
      return "TextCaption";
    case Significance::Information:
      return "Information";
    case Significance::Warning:
      return "Warning";
    case Significance::Error:
      return "Error";
    case Significance::Danger:
      return "Danger";
  }
  return "Unrecognized Significance";
}

enum class TextAlignment { Start, Center, End, Justify };

constexpr std::string ToString(const TextAlignment a) {
  switch (a) {
    case TextAlignment::Start:
      return "Start";
    case TextAlignment::Center:
      return "Center";
    case TextAlignment::End:
      return "End";
    case TextAlignment::Justify:
      return "Justify";
  }
  return "Unrecognized TextAlignment";
}

enum class TextTruncation { None, Clip, Ellipsis };

constexpr std::string ToString(const TextTruncation t) {
  switch (t) {
    case TextTruncation::None:
      return "None";
    case TextTruncation::Clip:
      return "Clip";
    case TextTruncation::Ellipsis:
      return "Ellipsis";
  }
  return "Unrecognized TextTruncation";
}

enum class TextWrap { None, Character, Word };

constexpr std::string ToString(const TextWrap w) {
  switch (w) {
    case TextWrap::None:
      return "None";
    case TextWrap::Character:
      return "Character";
    case TextWrap::Word:
      return "Word";
  }
  return "Unrecognized TextWrap";
}

enum class TextStyle : uint8_t {
  Regular = 0,
  Bold = 1 << 0,
  Italic = 1 << 1,
  BoldItalic = Bold | Italic,
  Monospace = 1 << 2,
};

constexpr std::string ToString(const TextStyle t) {
  switch (t) {
    case TextStyle::Regular:
      return "Regular";
    case TextStyle::Bold:
      return "Bold";
    case TextStyle::Italic:
      return "Italic";
    case TextStyle::BoldItalic:
      return "BoldItalic";
    case TextStyle::Monospace:
      return "Monospace";
  }
  return "Unrecognized TextStyle";
}

constexpr TextStyle operator&(TextStyle a, TextStyle b) {
  return static_cast<TextStyle>(static_cast<uint8_t>(a) &
                                static_cast<uint8_t>(b));
}

constexpr TextStyle operator|(TextStyle a, TextStyle b) {
  return static_cast<TextStyle>(static_cast<uint8_t>(a) |
                                static_cast<uint8_t>(b));
}
};  // namespace Pano

#endif  // INCLUDE_PANO_CONSTANTS_H_
