// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_RADIO_H_
#define INCLUDE_PANO_RADIO_H_

#include <Pano/button.h>
#include <Pano/constants.h>
#include <Pano/stack.h>

#include <map>
#include <string>
#include <vector>

namespace Pano {
// Forward Declaration
class RadioGroup;

class RadioButton : public Button {
 public:
  explicit RadioButton(RadioGroup* group)
      : Button(Icon::RadioButtonUnselected), group_(group) {
    setup();
  }
  RadioButton(RadioGroup* group, std::string text)
      : Button(text, Icon::RadioButtonUnselected), group_(group), text_(text) {
    setup();
  }
  RadioButton(RadioGroup* group, std::string text,
              std::function<void(bool)> on_changed)
      : Button(text, Icon::RadioButtonUnselected),
        OnChanged(on_changed),
        group_(group),
        text_(text) {
    setup();
  }

  RadioButton(const RadioButton&) = delete;
  RadioButton& operator=(const RadioButton&) = delete;
  RadioButton(RadioButton&&) = delete;
  RadioButton& operator=(RadioButton&&) = delete;

  // Get State
  bool IsSelected() const { return selected_; }
  std::string GetText() const { return text_; }

  // Set State
  void SetSelected(const bool selected) {
    selected_ = selected;
    SetIcon(selected_ ? Icon::RadioButtonSelected
                      : Icon::RadioButtonUnselected);
    if (const auto h{OnChanged}; h != nullptr) {
      OnChanged(selected_);
    }
  }

  std::function<void(bool)> OnChanged{nullptr};

 private:
  void setup();

  RadioGroup* group_{nullptr};
  std::string text_;
  bool selected_{false};
};

class RadioGroup : public StackLayout {
 public:
  RadioGroup() : StackLayout() {}
  explicit RadioGroup(const std::vector<std::string> options) : StackLayout() {
    SetOptions(options);
  }
  RadioGroup(const std::vector<std::string> options,
             std::function<void(std::string)> on_changed)
      : StackLayout(), OnChanged(on_changed) {
    SetOptions(options);
  }
  ~RadioGroup() { ClearViews(); }

  RadioGroup(const RadioGroup&) = delete;
  RadioGroup& operator=(const RadioGroup&) = delete;
  RadioGroup(RadioGroup&&) = delete;
  RadioGroup& operator=(RadioGroup&&) = delete;

  // Get State
  std::vector<std::string> GetOptions() const { return options_; }
  std::string GetSelection() const { return selection_; }
  RadioButton* GetRadioButton(const std::string& option) const {
    if (const auto it{buttons_.find(option)}; it != buttons_.end()) {
      return it->second;
    }
    return nullptr;
  }

  // Set State
  void SetOptions(const std::vector<std::string> options_);
  void SetSelectedRadio(const std::string& selection) {
    selection_ = selection;
    for (const auto& [k, v] : buttons_) {
      v->SetSelected(k == selection);
    }
    Redraw();
    if (const auto h{OnChanged}; h != nullptr) {
      OnChanged(selection_);
    }
  }
  void SetCondition(const Condition condition) override {
    for (const auto& [k, v] : buttons_) {
      v->SetCondition(condition);
    }
    Redraw();
  }
  void SetSignificance(const Significance significance) override {
    for (const auto& [k, v] : buttons_) {
      v->SetSignificance(significance);
    }
    Redraw();
  }
  void SetHorizontalAlignment(const Alignment alignment) override {
    for (const auto& [k, v] : buttons_) {
      v->SetHorizontalAlignment(alignment);
    }
    Redraw();
  }
  void SetVerticalAlignment(const Alignment alignment) override {
    for (const auto& [k, v] : buttons_) {
      v->SetVerticalAlignment(alignment);
    }
    Redraw();
  }
  void SetTextAlignment(const TextAlignment alignment) {
    for (const auto& [k, v] : buttons_) {
      v->SetTextAlignment(alignment);
    }
    Redraw();
  }
  void SetTextTruncation(const TextTruncation truncation) {
    for (const auto& [k, v] : buttons_) {
      v->SetTextTruncation(truncation);
    }
    Redraw();
  }
  void SetTextWrap(const TextWrap wrap) {
    for (const auto& [k, v] : buttons_) {
      v->SetTextWrap(wrap);
    }
    Redraw();
  }
  void SetTextStyle(const TextStyle style) {
    for (const auto& [k, v] : buttons_) {
      v->SetTextStyle(style);
    }
    Redraw();
  }
  void SetTextSize(const int size) {
    for (const auto& [k, v] : buttons_) {
      v->SetTextSize(size);
    }
    Redraw();
  }

  void ClearViews() override {
    StackLayout::ClearViews();
    for (auto it{buttons_.begin()}; it != buttons_.end(); ++it) {
      delete it->second;
    }
    buttons_.clear();
  }

  std::function<void(std::string)> OnChanged{nullptr};

 private:
  std::vector<std::string> options_;
  std::map<std::string, RadioButton*> buttons_;
  std::string selection_;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_RADIO_H_
