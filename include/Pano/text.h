// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_TEXT_H_
#define INCLUDE_PANO_TEXT_H_

#include <Pano/animation.h>
#include <Pano/constants.h>
#include <Pano/geometry.h>
#include <Pano/typesetting.h>
#include <Pano/view.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <chrono>
#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace Pano {
class TextView : public View {
 public:
  TextView() : View() {
    significance_ = Significance::TextBody;
    update_font();
  }
  explicit TextView(const std::string text) : TextView() { SetText(text); }
  ~TextView() {
    clear_glyphs();
    clear_typesetter();
  }

  TextView(const TextView&) = delete;
  TextView& operator=(const TextView&) = delete;
  TextView(TextView&&) = delete;
  TextView& operator=(TextView&&) = delete;

  // Get State
  Font* GetFont() const { return font_; }
  TextAlignment GetTextAlignment() const { return text_alignment_; }
  TextTruncation GetTextTruncation() const { return text_truncation_; }
  TextWrap GetTextWrap() const { return text_wrap_; }
  TextStyle GetTextStyle() const;
  int GetTextSize() const;
  std::string GetText() const {
    std::string text;
    for (const auto g : glyphs_) {
      text += g->GetText();
    }
    return text;
  }
  std::vector<UTFGlyph*> GetGlyphs() const { return glyphs_; }
  Size GetMinimumSize() const override;
  class TextViewArtist : public Artist {
   public:
    explicit TextViewArtist(TextView* view) : Artist(view) {}

    void Draw(SDL_Renderer*) override;
  };

  Artist* GetArtist() override {
    if (artist_ == nullptr) {
      artist_ = new TextViewArtist(this);
    }
    return View::GetArtist();
  }

  // Set State
  void SetFont(Font* font) {
    if (font_ != font) {
      font_ = font;
      clear_typesetter();
      Redraw();
    }
  }
  void SetHorizontalAlignment(const Alignment alignment) override {
    if (horizontal_alignment_ != alignment) {
      horizontal_alignment_ = alignment;
      clear_typesetter();
      View::SetHorizontalAlignment(alignment);
    }
  }
  void SetVerticalAlignment(const Alignment alignment) override {
    if (vertical_alignment_ != alignment) {
      vertical_alignment_ = alignment;
      clear_typesetter();
      View::SetVerticalAlignment(alignment);
    }
  }
  void SetTextAlignment(const TextAlignment alignment) {
    if (text_alignment_ != alignment) {
      text_alignment_ = alignment;
      clear_typesetter();
      Redraw();
    }
  }
  void SetTextTruncation(const TextTruncation truncation) {
    if (text_truncation_ != truncation) {
      text_truncation_ = truncation;
      clear_typesetter();
      Redraw();
    }
  }
  void SetTextWrap(const TextWrap wrap) {
    if (text_wrap_ != wrap) {
      text_wrap_ = wrap;
      clear_typesetter();
      Redraw();
    }
  }
  void SetTextStyle(const TextStyle style) {
    if (text_style_ != style) {
      text_style_override_ = true;
      text_style_ = style;
      clear_typesetter();
      update_font();
      Redraw();
    }
  }
  void ClearTextStyleOverride() {
    text_style_override_ = false;
    clear_typesetter();
    update_font();
    Redraw();
  }
  void SetTextSize(const int size) {
    if (text_size_ != size) {
      text_size_override_ = true;
      text_size_ = size;
      clear_typesetter();
      update_font();
      Redraw();
    }
  }
  void ClearTextSizeOverride() {
    text_size_override_ = false;
    clear_typesetter();
    update_font();
    Redraw();
  }
  void SetText(const std::string text) {
    clear_glyphs();
    glyphs_ = SplitUTF8(text);
    clear_typesetter();
    Redraw();
  }
  void ClearText() {
    clear_glyphs();
    clear_typesetter();
    Redraw();
  }
  void SetSize(const Size size) override {
    const auto max_width{static_cast<float>(size.width)};
    const auto max_height{static_cast<float>(size.height)};
    if (max_width_ != max_width || max_height_ != max_height) {
      max_width_ = max_width;
      max_height_ = max_height;
      clear_typesetter();
      View::SetSize(size);
    }
  }
  void SetMinimumLineLength(const float length) {
    if (min_line_length_ != length) {
      min_line_length_ = length;
      clear_typesetter();
      Redraw();
    }
  }

 protected:
  Typesetter* get_typesetter() {
    if (typesetter_ == nullptr) {
      typesetter_ =
          new Typesetter(font_, glyphs_, vertical_alignment_, text_alignment_,
                         text_truncation_, text_wrap_, max_width_, max_height_);
      typesetter_->Typeset();
    }
    return typesetter_;
  }
  std::vector<TextLine*> get_lines() {
    if (typesetter_ == nullptr) {
      return {};
    }
    return typesetter_->GetLines();
  }
  void update_font() {
    const auto fonts{App::current_->GetFontProvider()};
    const auto name{fonts->GetFontName()};
    const auto font{fonts->GetFont(name, text_style_, text_size_)};
    SetFont(font);
  }
  void clear_glyphs() {
    for (auto g : glyphs_) {
      delete g;
    }
    glyphs_.clear();
  }
  void clear_typesetter() {
    if (typesetter_ != nullptr) {
      delete typesetter_;
      typesetter_ = nullptr;
    }
  }

  Font* font_{nullptr};
  Alignment horizontal_alignment_{Alignment::Start};
  Alignment vertical_alignment_{Alignment::Start};
  TextAlignment text_alignment_{TextAlignment::Start};
  TextTruncation text_truncation_{TextTruncation::None};
  TextWrap text_wrap_{TextWrap::None};
  TextStyle text_style_{TextStyle::Regular};
  bool text_style_override_{false};
  int text_size_{16};
  bool text_size_override_{false};
  std::vector<UTFGlyph*> glyphs_;
  float min_line_length_{0};
  float max_width_{0};
  float max_height_{0};
  Typesetter* typesetter_{nullptr};
};

class TextEntry : public TextView, public Animation {
 public:
  TextEntry() : TextView() { setup(); }
  explicit TextEntry(std::string text) : TextView(text) { setup(); }
  ~TextEntry() { teardown(); }

  TextEntry(const TextEntry&) = delete;
  TextEntry& operator=(const TextEntry&) = delete;
  TextEntry(TextEntry&&) = delete;
  TextEntry& operator=(TextEntry&&) = delete;

  std::vector<View*> GetKeyboardableViews() override;
  class TextEntryArtist : public TextViewArtist {
   public:
    explicit TextEntryArtist(TextEntry* view) : TextViewArtist(view) {}

    void Draw(SDL_Renderer*) override;
  };

  Artist* GetArtist() override {
    if (artist_ == nullptr) {
      artist_ = new TextEntryArtist(this);
    }
    return View::GetArtist();
  }

  bool HandleKeyboardFocusGained() override;
  bool HandleKeyboardFocusLost() override;
  bool HandleKeyboardEvent(SDL_KeyboardEvent& e) override;
  bool HandleTextEditingEvent(SDL_TextEditingEvent& e) override;
  bool HandleTextInputEvent(SDL_TextInputEvent& e) override;

  bool Tick(const std::chrono::system_clock::time_point) override;
  std::function<void(std::string)> OnTextChanged{nullptr};

 protected:
  void setup();
  void teardown();
  bool cursor_active_{true};
  size_t cursor_pos_{0};
  size_t cursor_row_{0};
  size_t cursor_column_{0};
  /*
    size_t selectionStart_{0};
    size_t selectionEnd_{0};
  */
};
};  // namespace Pano

#endif  // INCLUDE_PANO_TEXT_H_
