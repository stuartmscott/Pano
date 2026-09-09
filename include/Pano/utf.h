// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_UTF_H_
#define INCLUDE_PANO_UTF_H_
#include <Pano/constants.h>

#include <string>
#include <vector>

namespace Pano {
void ToUTF8(const std::string& in, std::u8string& out);
void UTF8To32(const std::u8string& in, std::u32string& out);
void UTF32To8(const std::u32string& in, std::u8string& out);

class UTFGlyph {
 public:
  explicit UTFGlyph(std::string s) : s_(s) {}
  ~UTFGlyph() {}

  UTFGlyph(const UTFGlyph&) = delete;
  UTFGlyph& operator=(const UTFGlyph&) = delete;
  UTFGlyph(UTFGlyph&&) = delete;
  UTFGlyph& operator=(UTFGlyph&&) = delete;

  std::string GetText() const { return s_; }
  char32_t GetChar() const;
  bool IsNewLine() const { return GetChar() == NewLineChar; }

 private:
  std::string s_;
};

std::vector<UTFGlyph*> SplitUTF8(std::string s);

UTFGlyph* NextUTFGlyph(std::string::const_iterator& it,
                       const std::string::const_iterator& end);

char32_t NextUTFCodepoint(std::string::const_iterator& it,
                          const std::string::const_iterator& end);

bool IsUTFModifier(char32_t c);
};  // namespace Pano

#endif  // INCLUDE_PANO_UTF_H_
