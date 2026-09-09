// Copyright 2026 Stuart Scott
#include <Pano/app.h>
#include <Pano/color.h>
#include <Pano/constants.h>
#include <Pano/font.h>
#include <Pano/log.h>
#include <Pano/text.h>
#include <Pano/typesetting.h>
#include <Pano/utf.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <algorithm>
#include <cstring>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace Pano {

TextStyle TextView::GetTextStyle() const {
  if (text_style_override_) {
    return text_style_;
  }
  switch (significance_) {
    case Significance::TextTitle:
    case Significance::TextHeading1:
    case Significance::TextHeading2:
    case Significance::TextHeading3:
    case Significance::TextHeading4:
    case Significance::TextHeading5:
    case Significance::TextHeading6:
      return TextStyle::Bold;
    case Significance::TextSubtitle:
      return TextStyle::Italic;
    case Significance::TextCaption:
      return TextStyle::BoldItalic;
    default:
      return TextStyle::Regular;
  }
}

int TextView::GetTextSize() const {
  if (text_size_override_) {
    return text_size_;
  }
  switch (significance_) {
    case Significance::TextTitle:
      return 120;
    case Significance::TextHeading1:
      return 96;
    case Significance::TextHeading2:
      return 60;
    case Significance::TextHeading3:
      return 48;
    case Significance::TextHeading4:
      return 34;
    case Significance::TextHeading5:
      return 24;
    case Significance::TextHeading6:
      return 20;
    case Significance::TextSubtitle:
      return 16;
    case Significance::TextCaption:
      return 12;
    default:
      return 16;
  }
}

Size TextView::GetMinimumSize() const {
  if (font_ == nullptr) {
    return {};
  }

  // TODO recalculate only when glyphs_, font_, wrap_ or truncation_ changes

  const float font_height{static_cast<float>(font_->GetHeight())};
  const float font_line_skip{static_cast<float>(font_->GetLineSkip())};

  if (glyphs_.empty() || (glyphs_.size() == 1 && glyphs_.back()->IsNewLine())) {
    return {min_line_length_, static_cast<float>(font_height)};
  }

  switch (text_truncation_) {
    case TextTruncation::None: {
      switch (text_wrap_) {
        case TextWrap::None: {
          // Create lines as long as possible only breaking because of newline
          // characters
          Typesetter ts(font_, glyphs_, vertical_alignment_, text_alignment_,
                        text_truncation_, text_wrap_,
                        std::numeric_limits<float>::max(),
                        std::numeric_limits<float>::max());
          ts.Typeset();
          const auto lines{ts.GetLines()};
          // Find the longest line
          float max_line_width{0};
          for (const auto& line : lines) {
            const auto w{line->GetSize().width};
            if (w > max_line_width) {
              max_line_width = w;
            }
          }
          return {max_line_width, lines.size() * font_line_skip};
        }
        case TextWrap::Character:
        case TextWrap::Word: {
          // Create lines as long and the minimum line length
          Typesetter ts(font_, glyphs_, vertical_alignment_, text_alignment_,
                        text_truncation_, text_wrap_, min_line_length_,
                        std::numeric_limits<float>::max());
          ts.Typeset();
          const auto lines{ts.GetLines()};
          // Find the longest line
          float max_line_width{0};
          for (const auto& line : lines) {
            const auto w{line->GetSize().width};
            if (w > max_line_width) {
              max_line_width = w;
            }
          }
          return {max_line_width, lines.size() * font_line_skip};
        }
      }
      return {};
    }
    case TextTruncation::Clip:
      return {min_line_length_, font_height};
    case TextTruncation::Ellipsis:
      int min_x;
      int max_x;
      int min_y;
      int max_y;
      int advance;
      font_->GetMetrics(HorizontalEllipsisChar, &min_x, &max_x, &min_y, &max_y,
                        &advance);
      return {std::max(min_line_length_, static_cast<float>(max_x - min_x)),
              font_height};
  }
}

void TextView::TextViewArtist::Draw(SDL_Renderer* renderer) {
  View::Artist::Draw(renderer);

  if (texture_ == nullptr) {
    return;
  }

  const auto tv{static_cast<TextView*>(view_)};
  const auto ts{tv->get_typesetter()};

  const auto color{tv->GetColor(Layer::Foreground)};
  for (auto& line : ts->GetLines()) {
    if (!SDL_SetRenderTarget(renderer, texture_)) {
      Error() << "Failed to set render target: " << SDL_GetError() << std::endl;
    }
    if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
      Error() << "Failed to set blend mode: " << SDL_GetError() << std::endl;
    }
    if (!SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND)) {
      Error() << "Failed to set blend mode: " << SDL_GetError() << std::endl;
    }

    line->Draw(renderer, color);
  }
}

std::vector<View*> TextEntry::GetKeyboardableViews() { return {this}; }

bool TextEntry::HandleKeyboardFocusGained() {
  has_keyboard_focus_ = true;
  if (window_ != nullptr && !SDL_StartTextInput(window_->window_)) {
    // TODO SDL_StartTextInputWithProperties(SDL_Window *window,
    // SDL_PropertiesID props)
    // TODO SDL_SetTextInputArea(SDL_Window *window, const SDL_Rect *rect, int
    // cursor)
    Error() << "Failed to start text input: " << SDL_GetError() << std::endl;
  }
  return true;
}

bool TextEntry::HandleKeyboardFocusLost() {
  has_keyboard_focus_ = false;
  if (window_ != nullptr && !SDL_StopTextInput(window_->window_)) {
    Error() << "Failed to stop text input: " << SDL_GetError() << std::endl;
  }
  return true;
}

bool TextEntry::HandleKeyboardEvent(SDL_KeyboardEvent& e) {
  switch (e.type) {
    case SDL_EVENT_KEY_DOWN: {
      switch (e.key) {
        case SDLK_BACKSPACE: {
          const auto size = glyphs_.size();
          const auto cursor{std::min(cursor_pos_, size)};
          if (size > 0 && cursor > 0) {
            cursor_pos_ = cursor - 1;
            delete glyphs_[cursor_pos_];
            glyphs_.erase(glyphs_.begin() + cursor_pos_);
            clear_typesetter();
            Redraw();
          }
          return true;
        }
        case SDLK_RETURN: {
          const auto cursor{std::min(cursor_pos_, glyphs_.size())};
          glyphs_.insert(glyphs_.begin() + cursor,
                         new UTFGlyph(std::string{NewLineChar}));
          cursor_pos_ = cursor + 1;
          clear_typesetter();
          Redraw();
          return true;
        }
        case SDLK_UP: {
          const auto& lines{get_lines()};
          if (!lines.empty() && cursor_row_ > 0) {
            cursor_pos_ -= std::min(cursor_pos_,
                                    lines[cursor_row_ - 1]->GetGlyphs().size());
            Redraw();
          }
          return true;
        }
        case SDLK_DOWN: {
          const auto& lines{get_lines()};
          if (cursor_row_ < lines.size() - 1) {
            cursor_pos_ =
                std::min(glyphs_.size(),
                         cursor_pos_ + lines[cursor_row_]->GetGlyphs().size());
            Redraw();
          }
          return true;
        }
        case SDLK_LEFT: {
          if (cursor_pos_ > 0) {
            cursor_pos_--;
            Redraw();
          }
          return true;
        }
        case SDLK_RIGHT: {
          if (cursor_pos_ < glyphs_.size()) {
            cursor_pos_++;
            Redraw();
          }
          return true;
        }
      }
      break;
    }
    default:
      break;
  }
  return false;
}

bool TextEntry::HandleTextEditingEvent(SDL_TextEditingEvent& e) { return true; }

bool TextEntry::HandleTextInputEvent(SDL_TextInputEvent& e) {
  const auto cursor{std::min(cursor_pos_, glyphs_.size())};
  const auto gs = SplitUTF8(e.text);
  glyphs_.insert(glyphs_.begin() + cursor, gs.begin(), gs.end());
  cursor_pos_ = cursor + gs.size();
  clear_typesetter();
  Redraw();
  return true;
}

void TextEntry::setup() {
  cursor_pos_ = glyphs_.size();
  App::current_->AddAnimation(this);
}

void TextEntry::teardown() { App::current_->RemoveAnimation(this); }

bool TextEntry::Tick(const std::chrono::system_clock::time_point t) {
  const auto active{
      (std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch())
           .count() %
       2) == 0};
  if (cursor_active_ != active) {
    cursor_active_ = active;
    Redraw();
  }
  return true;
}

void TextEntry::TextEntryArtist::Draw(SDL_Renderer* renderer) {
  TextView::TextViewArtist::Draw(renderer);

  const auto te = static_cast<TextEntry*>(view_);
  if (texture_ == nullptr || !IsBitSet(te->condition_, Condition::Enabled) ||
      !te->has_keyboard_focus_) {
    return;
  }

  const auto lines{te->get_lines()};

  te->cursor_row_ = 0;
  te->cursor_column_ = 0;
  size_t cursor_pos{te->cursor_pos_};
  for (const auto& line : lines) {
    const auto size{line->GetGlyphs().size()};
    if (cursor_pos > size) {
      te->cursor_row_++;
      cursor_pos -= size;
    } else {
      te->cursor_column_ = cursor_pos;
    }
  }
  Debug() << "Cursor Pos: " << te->cursor_pos_ << std::endl;
  Debug() << "Cursor Row: " << te->cursor_row_ << std::endl;
  Debug() << "Cursor Col: " << te->cursor_column_ << std::endl;

  if (te->cursor_row_ >= lines.size()) {
    return;
  }

  // Draw cursor
  if (!SDL_SetRenderTarget(renderer, texture_)) {
    Error() << "Failed to set render target: " << SDL_GetError() << std::endl;
  }

  if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
    Error() << "Failed to set blend mode: " << SDL_GetError() << std::endl;
  }

  const auto layer = te->cursor_active_ ? Layer::Foreground : Layer::Background;
  const auto colors{App::current_->GetColorProvider()};
  const auto color =
      colors->GetColor(Significance::Primary, Condition::Enabled, layer);
  if (!SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a)) {
    Error() << "Failed to set draw color: " << SDL_GetError() << std::endl;
  }

  const auto line{lines[te->cursor_row_]};
  Point char_position{line->GetPosition(te->cursor_column_)};
  SDL_FRect rect{static_cast<float>(char_position.x - 1), char_position.y, 3,
                 static_cast<float>(te->font_->GetHeight())};
  if (!SDL_RenderFillRect(renderer, &rect)) {
    Error() << "Failed to fill rectangle: " << SDL_GetError() << std::endl;
  }
}
};  // namespace Pano
