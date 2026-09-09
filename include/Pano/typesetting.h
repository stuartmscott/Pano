// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_TYPESETTING_H_
#define INCLUDE_PANO_TYPESETTING_H_

#include <Pano/app.h>
#include <Pano/font.h>
#include <Pano/log.h>
#include <Pano/utf.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <vector>

namespace Pano {
class TextLine {
 public:
  TextLine(Font* font, std::vector<UTFGlyph*> glyphs)
      : font_(font), glyphs_(glyphs) {}
  ~TextLine() {}

  TextLine(const TextLine&) = delete;
  TextLine& operator=(const TextLine&) = delete;
  TextLine(TextLine&& other) = delete;
  TextLine& operator=(TextLine&& other) = delete;

  Font* GetFont() const { return font_; }
  std::string GetText() const {
    std::string text;
    for (const auto g : glyphs_) {
      text += g->GetText();
    }
    return text;
  }
  std::vector<UTFGlyph*> GetGlyphs() const { return glyphs_; }
  bool Empty() const { return glyphs_.empty(); }
  Point GetPosition(size_t cursor) const;
  Size GetSize() const;

  bool HasHorizontalEllipsis() const { return horizontal_ellipsis_; }
  bool HasVerticalEllipsis() const { return vertical_ellipsis_; }
  bool HasHyphen() const { return hyphen_; }

  void AddHorizontalEllipsis() {
    Debug() << "Horizontal Ellipsis added" << std::endl;
    horizontal_ellipsis_ = true;
    vertical_ellipsis_ = false;
    hyphen_ = false;
  }
  void AddVerticalEllipsis() {
    Debug() << "Vertical Ellipsis added" << std::endl;
    horizontal_ellipsis_ = false;
    vertical_ellipsis_ = true;
    hyphen_ = false;
  }
  void AddHyphen() {
    Debug() << "Hyphen added" << std::endl;
    horizontal_ellipsis_ = false;
    vertical_ellipsis_ = false;
    hyphen_ = true;
  }

  void Layout(const Point position, const float total_tracking);

  void DropLastGlyph();

  void Draw(SDL_Renderer*, const SDL_Color color);

 private:
  Font* font_{nullptr};
  std::vector<UTFGlyph*> glyphs_;
  std::vector<Point> positions_;
  bool horizontal_ellipsis_{false};
  bool vertical_ellipsis_{false};
  bool hyphen_{false};
};

class Typesetter {
 public:
  Typesetter(Font* font, std::vector<UTFGlyph*> glyphs,
             Alignment line_alignment, TextAlignment text_alignment,
             TextTruncation text_truncation, TextWrap text_wrap,
             float max_width, float max_height)
      : font_(font),
        glyphs_(glyphs),
        line_alignment_(line_alignment),
        text_alignment_(text_alignment),
        text_truncation_(text_truncation),
        text_wrap_(text_wrap),
        max_width_(max_width),
        max_height_(max_height) {
    max_lines_ = static_cast<uint32_t>(max_height / font->GetHeight());
  }
  ~Typesetter() { clear_lines(); }

  Typesetter(const Typesetter&) = delete;
  Typesetter& operator=(const Typesetter&) = delete;
  Typesetter(Typesetter&&) = delete;
  Typesetter& operator=(Typesetter&&) = delete;

  std::vector<TextLine*> GetLines() const { return lines_; }

  void Typeset();

 private:
  void create_lines();
  void layout_lines();
  bool line_break(const std::vector<UTFGlyph*>::const_iterator line_end);
  void add_ellipsis_to_last_line();
  void add_hyphen_to_last_line();
  void clear_lines() {
    for (auto l : lines_) {
      delete l;
    }
    lines_.clear();
  }

  Font* font_{nullptr};
  std::vector<UTFGlyph*> glyphs_;
  Alignment line_alignment_{Alignment::Start};
  TextAlignment text_alignment_{TextAlignment::Start};
  TextTruncation text_truncation_{TextTruncation::Ellipsis};
  TextWrap text_wrap_{TextWrap::None};
  float max_width_{0};
  float max_height_{0};
  uint32_t max_lines_{0};
  std::vector<UTFGlyph*>::const_iterator glyph_it_;
  std::vector<UTFGlyph*>::const_iterator glyph_end_;
  std::vector<UTFGlyph*>::const_iterator line_start_;
  std::vector<UTFGlyph*>::const_iterator last_space_;
  char32_t previous_char_{0};
  char32_t current_char_{0};
  int cursor_{0};
  std::vector<TextLine*> lines_;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_TYPESETTING_H_
