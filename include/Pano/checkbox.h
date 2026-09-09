// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_CHECKBOX_H_
#define INCLUDE_PANO_CHECKBOX_H_

#include <Pano/button.h>

#include <string>

namespace Pano {
class CheckBox : public Button {
 public:
  CheckBox() : Button(Icon::CheckBoxUnchecked) { setup(); }
  explicit CheckBox(const std::string text)
      : Button(text, Icon::CheckBoxUnchecked) {
    setup();
  }
  CheckBox(const std::string text, const std::function<void(bool)> on_changed)
      : Button(text, Icon::CheckBoxUnchecked), OnChanged(on_changed) {
    setup();
  }

  CheckBox(const CheckBox&) = delete;
  CheckBox& operator=(const CheckBox&) = delete;
  CheckBox(CheckBox&&) = delete;
  CheckBox& operator=(CheckBox&&) = delete;

  // Get State
  bool IsChecked() const { return checked_; }

  // Set State
  void SetChecked(const bool checked) {
    checked_ = checked;
    SetIcon(checked_ ? Icon::CheckBoxChecked : Icon::CheckBoxUnchecked);
    if (const auto h{OnChanged}; h != nullptr) {
      OnChanged(checked_);
    }
  }

  std::function<void(bool)> OnChanged{nullptr};

 private:
  void setup();

  bool checked_{false};
};
};  // namespace Pano

#endif  // INCLUDE_PANO_CHECKBOX_H_
