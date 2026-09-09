// Copyright 2026 Stuart Scott
#include <Pano/log.h>
#include <Pano/utf.h>

#include <iostream>
#include <string>
#include <vector>

namespace Pano {

void ToUTF8(const std::string& in, std::u8string& out) {
  for (auto it{in.cbegin()}; it != in.cend(); ++it) {
    out += static_cast<char8_t>(*it);
  }
}

/*
https://en.wikipedia.org/wiki/UTF-8
First      Last       Byte 1   Byte 2   Byte 3   Byte 4
U+00000000 U+0000007F 0yyyzzzz
U+00000080 U+000007FF 110xxxyy 10yyzzzz
U+00000800 U+0000FFFF 1110wwww 10xxxxyy 10yyzzzz
U+00010000 U+0010FFFF 11110uvv 10vvwwww 10xxxxyy 10yyzzzz
*/

void UTF8To32(const std::u8string& in, std::u32string& out) {
  for (auto it{in.cbegin()}; it != in.cend();) {
    const auto w{static_cast<char32_t>(*it)};

    // Check MSB1
    if ((w & 0x80) == 0) {
      out += w;
      ++it;
      continue;
    }

    // Ensure MSB2 is 1
    if ((w & 0x40) != 0x40) {
      Error() << "Invalid UTF8" << std::endl;
      return;
    }

    // Check MSB3
    if ((w & 0x20) == 0) {
      ++it;
      const auto x{static_cast<char32_t>(*it)};
      // Ensure MSB1 is 1 and MSB2 is 0
      if ((x & 0xC0) != 0x80) {
        Error() << "Invalid UTF8" << std::endl;
        return;
      }
      out += ((w & 0x1F) << 6) | (x & 0x3F);
      ++it;
      continue;
    }

    // Check MSB4
    if ((w & 0x10) == 0) {
      ++it;
      const auto x{static_cast<char32_t>(*it)};
      // Ensure MSB1 is 1 and MSB2 is 0
      if ((x & 0xC0) != 0x80) {
        Error() << "Invalid UTF8" << std::endl;
        return;
      }
      ++it;
      const auto y{static_cast<char32_t>(*it)};
      // Ensure MSB1 is 1 and MSB2 is 0
      if ((y & 0xC0) != 0x80) {
        Error() << "Invalid UTF8" << std::endl;
        return;
      }
      out += ((w & 0xF) << 12) | ((x & 0x3F) << 6) | (y & 0x3F);
      ++it;
      continue;
    }

    // Ensure MSB5 is 0
    if ((w & 0x8) != 0) {
      Error() << "Invalid UTF8" << std::endl;
      return;
    }

    ++it;
    const auto x{static_cast<char32_t>(*it)};
    // Ensure MSB1 is 1 and MSB2 is 0
    if ((x & 0xC0) != 0x80) {
      Error() << "Invalid UTF8" << std::endl;
      return;
    }
    ++it;
    const auto y{static_cast<char32_t>(*it)};
    // Ensure MSB1 is 1 and MSB2 is 0
    if ((y & 0xC0) != 0x80) {
      Error() << "Invalid UTF8" << std::endl;
      return;
    }
    ++it;
    const auto z{static_cast<char32_t>(*it)};
    // Ensure MSB1 is 1 and MSB2 is 0
    if ((z & 0xC0) != 0x80) {
      Error() << "Invalid UTF8" << std::endl;
      return;
    }
    out +=
        ((w & 0x7) << 18) | ((x & 0x3F) << 12) | ((y & 0x3F) << 6) | (z & 0x3F);
    ++it;
  }
}

void UTF32To8(const std::u32string& in, std::u8string& out) {
  for (auto it{in.cbegin()}; it != in.cend();) {
    const char32_t c{*it};

    // 1 Byte
    if ((c & 0xFFFFFF80) == 0) {
      out += static_cast<char8_t>(c);
      ++it;
      continue;
    }

    // 2 Bytes
    if ((c & 0xFFFFF800) == 0) {
      out += static_cast<char8_t>(0xC0 | ((c & 0x7C0) >> 6));
      out += static_cast<char8_t>(0x80 | (c & 0x3F));
      ++it;
      continue;
    }

    // 3 Bytes
    if ((c & 0xFFF10000) == 0) {
      out += static_cast<char8_t>(0xE0 | ((c & 0xF000) >> 12));
      out += static_cast<char8_t>(0x80 | ((c & 0xFC0) >> 6));
      out += static_cast<char8_t>(0x80 | (c & 0x3F));
      ++it;
      continue;
    }

    // 4 Bytes
    out += static_cast<char8_t>(0xF0 | ((c & 0x1C0000) >> 18));
    out += static_cast<char8_t>(0x80 | ((c & 0x3F000) >> 12));
    out += static_cast<char8_t>(0x80 | ((c & 0xFC0) >> 6));
    out += static_cast<char8_t>(0x80 | (c & 0x3F));
    ++it;
  }
}

char32_t UTFGlyph::GetChar() const {
  if (s_.empty()) {
    return 0;
  }
  auto it = s_.cbegin();
  return NextUTFCodepoint(it, s_.cend());
}

std::vector<UTFGlyph*> SplitUTF8(std::string s) {
  std::vector<UTFGlyph*> glyphs;
  auto it = s.cbegin();
  const auto end = s.cend();
  while (it != end) {
    const auto g = NextUTFGlyph(it, end);
    if (g == nullptr) {
      break;
    }
    glyphs.push_back(g);
  }
  return glyphs;
}

UTFGlyph* NextUTFGlyph(std::string::const_iterator& it,
                       const std::string::const_iterator& end) {
  const auto start = it;
  auto next = it;
  const auto c = NextUTFCodepoint(next, end);
  if (c == 0) {
    return nullptr;
  }
  it = next;
  while (it != end) {
    auto next = it;
    const auto c = NextUTFCodepoint(next, end);
    if (c > 0 && IsUTFModifier(c)) {
      it = next;
    } else {
      break;
    }
  }
  return new UTFGlyph(std::string{start, it});
}

char32_t NextUTFCodepoint(std::string::const_iterator& it,
                          const std::string::const_iterator& end) {
  // Increment it to next UTF and return parsed codepoint
  const auto w{static_cast<char32_t>(*it)};

  // Check MSB1
  if ((w & 0x80) == 0) {
    ++it;
    return w;
  }

  // Ensure MSB2 is 1
  if ((w & 0x40) != 0x40) {
    Error() << "Invalid UTF8" << std::endl;
    return 0;
  }

  // Check MSB3
  if ((w & 0x20) == 0) {
    ++it;
    if (it == end) {
      Error() << "Invalid UTF8" << std::endl;
      return 0;
    }
    const auto x{static_cast<char32_t>(*it)};
    // Ensure MSB1 is 1 and MSB2 is 0
    if ((x & 0xC0) != 0x80) {
      Error() << "Invalid UTF8" << std::endl;
      return 0;
    }
    ++it;
    return ((w & 0x1F) << 6) | (x & 0x3F);
  }

  // Check MSB4
  if ((w & 0x10) == 0) {
    ++it;
    if (it == end) {
      Error() << "Invalid UTF8" << std::endl;
      return 0;
    }
    const auto x{static_cast<char32_t>(*it)};
    // Ensure MSB1 is 1 and MSB2 is 0
    if ((x & 0xC0) != 0x80) {
      Error() << "Invalid UTF8" << std::endl;
      return 0;
    }
    ++it;
    if (it == end) {
      Error() << "Invalid UTF8" << std::endl;
      return 0;
    }
    const auto y{static_cast<char32_t>(*it)};
    // Ensure MSB1 is 1 and MSB2 is 0
    if ((y & 0xC0) != 0x80) {
      Error() << "Invalid UTF8" << std::endl;
      return 0;
    }
    ++it;
    return ((w & 0xF) << 12) | ((x & 0x3F) << 6) | (y & 0x3F);
  }

  // Ensure MSB5 is 0
  if ((w & 0x8) != 0) {
    Error() << "Invalid UTF8" << std::endl;
    return 0;
  }

  ++it;
  if (it == end) {
    Error() << "Invalid UTF8" << std::endl;
    return 0;
  }
  const auto x{static_cast<char32_t>(*it)};
  // Ensure MSB1 is 1 and MSB2 is 0
  if ((x & 0xC0) != 0x80) {
    Error() << "Invalid UTF8" << std::endl;
    return 0;
  }
  ++it;
  if (it == end) {
    Error() << "Invalid UTF8" << std::endl;
    return 0;
  }
  const auto y{static_cast<char32_t>(*it)};
  // Ensure MSB1 is 1 and MSB2 is 0
  if ((y & 0xC0) != 0x80) {
    Error() << "Invalid UTF8" << std::endl;
    return 0;
  }
  ++it;
  if (it == end) {
    Error() << "Invalid UTF8" << std::endl;
    return 0;
  }
  const auto z{static_cast<char32_t>(*it)};
  // Ensure MSB1 is 1 and MSB2 is 0
  if ((z & 0xC0) != 0x80) {
    Error() << "Invalid UTF8" << std::endl;
    return 0;
  }
  ++it;
  return ((w & 0x7) << 18) | ((x & 0x3F) << 12) | ((y & 0x3F) << 6) |
         (z & 0x3F);
}

bool IsUTFModifier(char32_t c) {
  // Spacing Modifier Letters
  if (c >= U'\U000002B0' && c <= U'\U000002FF') {
    return true;
  }

  // Nonspacing Marks (Diacritical Marks)
  if (c >= U'\U00000300' && c <= U'\U0000036F') {
    return true;
  }

  // Mongolian Variant Selectors
  if (c >= U'\U0000180B' && c <= U'\U0000180F') {
    return true;
  }

  // Joining
  if (c == U'\U0000200C' || c == U'\U0000200D') {
    return true;
  }

  // Variant Selector
  if (c >= U'\U0000FE00' && c <= U'\U0000FE0F') {
    return true;
  }

  // Emoji Modifier
  if (c >= U'\U0001F3FB' && c <= U'\U0001F3FF') {
    return true;
  }

  // Variant Selector Supplement
  if (c >= U'\U000E0100' && c <= U'\U000E01EF') {
    return true;
  }

  return false;
}
};  // namespace Pano
