// Copyright 2026 Stuart Scott
#include <Pano/log.h>
#include <Pano/text.h>
#include <Pano/typesetting.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <vector>

namespace Pano {

Point TextLine::GetPosition(size_t cursor) const {
  if (positions_.empty()) {
    return {0, 0};
  }

  if (cursor == 0) {
    return positions_.front();
  }

  if (cursor <= glyphs_.size()) {
    Point p{positions_[cursor - 1]};
    p.x += font_->GetAdvance(glyphs_[cursor - 1]->GetChar());
    return p;
  }

  Point p{positions_.back()};
  if (horizontal_ellipsis_) {
    p.x += font_->GetAdvance(HorizontalEllipsisChar);
  } else if (vertical_ellipsis_) {
    p.x += font_->GetAdvance(VerticalEllipsisChar);
  } else if (hyphen_) {
    p.x += font_->GetAdvance(HyphenChar);
  }
  return p;
}

Size TextLine::GetSize() const {
  float width{0};
  char32_t previous_char{0};
  for (const auto g : glyphs_) {
    const auto current_char = g->GetChar();
    if (current_char == NewLineChar) {
      break;
    }
    if (previous_char != 0) {
      width -= font_->GetKerning(previous_char, current_char);
    }
    width += font_->GetAdvance(current_char);
    previous_char = current_char;
  }
  if (horizontal_ellipsis_) {
    width += font_->GetAdvance(HorizontalEllipsisChar);
  } else if (vertical_ellipsis_) {
    width += font_->GetAdvance(VerticalEllipsisChar);
  } else if (hyphen_) {
    width += font_->GetAdvance(HyphenChar);
  }
  return {width, static_cast<float>(font_->GetHeight())};
}

void TextLine::DropLastGlyph() {
  if (glyphs_.empty()) {
    return;
  }
  glyphs_.pop_back();
}

void TextLine::Layout(const Point position, const float total_tracking) {
  positions_.clear();
  if (glyphs_.empty()) {
    return;
  }
  auto count{glyphs_.size()};
  if (horizontal_ellipsis_ || vertical_ellipsis_ || hyphen_) {
    ++count;
  }
  float x{position.x};
  // TODO add half tracking
  const auto tracking{total_tracking / (count - 1)};
  for (size_t i{0}; i < count; ++i) {
    if (i > 0) {
      x += font_->GetAdvance(glyphs_[i - 1]->GetChar()) + tracking;
    }
    positions_.emplace_back(x, position.y);
  }
}

void TextLine::Draw(SDL_Renderer* renderer, SDL_Color color) {
  const auto count{glyphs_.size()};
  for (size_t i{0}; i < count; ++i) {
    const auto g{glyphs_[i]};
    if (g->IsNewLine()) {
      break;
    }
    font_->Draw(renderer, g->GetText(), positions_[i], color);
  }

  if (horizontal_ellipsis_) {
    font_->Draw(renderer, HorizontalEllipsisString, positions_.back(), color);
  } else if (vertical_ellipsis_) {
    font_->Draw(renderer, VerticalEllipsisString, positions_.back(), color);
  } else if (hyphen_) {
    font_->Draw(renderer, HyphenString, positions_.back(), color);
  }
}

void Typesetter::Typeset() {
  clear_lines();

  if (font_ == nullptr) {
    return;
  }

  create_lines();

  layout_lines();
}

void Typesetter::create_lines() {
  glyph_it_ = glyphs_.cbegin();
  glyph_end_ = glyphs_.cend();
  line_start_ = glyph_it_;
  last_space_ = glyph_end_;

  previous_char_ = 0;

  cursor_ = 0;

  while (glyph_it_ != glyph_end_ && lines_.size() < max_lines_) {
    current_char_ = (*glyph_it_)->GetChar();

    if (current_char_ == NewLineChar) {
      if (!line_break(glyph_it_ + 1)) {
        return;
      }
      ++glyph_it_;
      continue;
    }

    if (current_char_ == SpaceChar) {
      last_space_ = glyph_it_;
    }

    int min_x{0};
    int max_x{0};
    int min_y{0};
    int max_y{0};
    int advance{0};
    font_->GetMetrics(current_char_, &min_x, &max_x, &min_y, &max_y, &advance);

    if (previous_char_ == 0) {
      const auto end{max_x};
      if (end > max_width_) {
        // Uh Oh!
        Error() << "View too small - truncation required" << std::endl;
        return;
      } else {
        // Can fit on current line
        previous_char_ = current_char_;
        cursor_ += advance;
        ++glyph_it_;
        continue;
      }
    }

    const auto kerning{font_->GetKerning(previous_char_, current_char_)};
    cursor_ -= kerning;
    const auto end{cursor_ + max_x};
    if (end > max_width_) {
      // Can't fit on current line
      switch (text_wrap_) {
        case TextWrap::None: {
          const auto success{line_break(glyph_it_)};
          switch (text_truncation_) {
            case TextTruncation::None:
              // Uh Oh!
              Error() << "View too small - truncation required" << std::endl;
              return;
            case TextTruncation::Clip:
              return;
            case TextTruncation::Ellipsis:
              if (success) {
                add_ellipsis_to_last_line();
              }
              return;
          }
        }
        case TextWrap::Character: {
          if (!line_break(glyph_it_)) {
            return;
          }
          continue;
        }
        case TextWrap::Word: {
          if (last_space_ != glyph_end_) {
            // Break at last space
            glyph_it_ = last_space_ + 1;
            if (!line_break(glyph_it_)) {
              return;
            }
          } else {
            // No previous space, break at character boundary and add hyphen
            --glyph_it_;
            if (line_break(glyph_it_)) {
              add_hyphen_to_last_line();
            } else {
              return;
            }
          }
          continue;
        }
      }
    } else {
      // Can fit on current line
      previous_char_ = current_char_;
      cursor_ += advance;
      ++glyph_it_;
    }
  }

  // Add any remaining characters
  if (line_start_ != glyph_end_) {
    if (lines_.size() < max_lines_) {
      line_break(glyph_it_);
    } else if (!lines_.empty() &&
               text_truncation_ == TextTruncation::Ellipsis) {
      add_ellipsis_to_last_line();
    }
  }
}

void Typesetter::layout_lines() {
  Point position{};

  auto block_height{static_cast<float>(lines_.size() * font_->GetLineSkip())};

  switch (line_alignment_) {
    case Alignment::Start:
      position.y = 0;
      break;
    case Alignment::Center:
      position.y = (max_height_ - block_height) / 2;
      break;
    case Alignment::End:
      position.y = max_height_ - block_height;
      break;
  }

  const auto count = lines_.size();
  for (size_t i{0}; i < count; ++i) {
    const auto line = lines_[i];
    Size size{line->GetSize()};
    float total_tracking{0};
    switch (text_alignment_) {
      case TextAlignment::Start:
        position.x = 0;
        break;
      case TextAlignment::Justify:
        position.x = 0;
        if (i < count - 1) {
          // Justify all but the last line
          total_tracking = max_width_ - size.width;
        }
        break;
      case TextAlignment::Center:
        position.x = (max_width_ - size.width) / 2;
        break;
      case TextAlignment::End:
        position.x = max_width_ - size.width;
        break;
    }
    line->Layout(position, total_tracking);
    position.y += font_->GetLineSkip();
  }
}

bool Typesetter::line_break(std::vector<UTFGlyph*>::const_iterator line_end) {
  bool result{false};
  const auto count{lines_.size()};
  if (count == max_lines_) {
    if (count > 0 && text_truncation_ == TextTruncation::Ellipsis) {
      add_ellipsis_to_last_line();
    }
  } else {
    lines_.push_back(
        new TextLine(font_, std::vector<UTFGlyph*>{line_start_, line_end}));
    result = true;
  }
  line_start_ = line_end;
  last_space_ = glyph_end_;
  previous_char_ = 0;
  cursor_ = 0;
  return result;
}

void Typesetter::add_ellipsis_to_last_line() {
  if (lines_.empty()) {
    return;
  }

  const auto& last{lines_.back()};
  if (last->Empty()) {
    last->AddVerticalEllipsis();
  } else {
    last->DropLastGlyph();
    // TODO if dropped glyph is narrower than Horizontal Ellipsis, drop another
    last->AddHorizontalEllipsis();
  }
}

void Typesetter::add_hyphen_to_last_line() {
  if (lines_.empty()) {
    return;
  }

  lines_.back()->AddHyphen();
}
};  // namespace Pano
