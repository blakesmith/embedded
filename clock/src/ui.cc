#include "ui.h"

namespace clock {

UI::UI(Display7Seg* display,
       Pec11RotaryEncoder* encoder)
    : display_(display),
      encoder_(encoder),
      knob_offset_(0),
      set_position_(3),
      update_count_(0),
      colon_toggle_(true)
{ }

void UI::Clear() {
    display_->Clear();
}

void UI::ToggleColon(bool on) {
    display_->ToggleColon(on);
}

void UI::SetHour(uint8_t hour) {
    display_->SetNumber(0, hour, 2, false);
}

void UI::SetMinute(uint8_t minute) {
    display_->SetNumber(3, minute, 2, true);
}

void UI::Update() {
    encoder_->ReadState();
    if (encoder_->GetButtonAction() == BUTTON_ACTION_DOWN) {
        set_position_ = (set_position_ + 1) % 4;
    }
    if (update_count_ == 0) {
        if (set_position_ != 3) {
            display_->SetSegment(set_position_ * 2, 0, false, true);
        }
        display_->ToggleColon(colon_toggle_);
        colon_toggle_ = !colon_toggle_;
        display_->WriteDisplay();
    }
    update_count_ = (update_count_ + 1) % 9000;
}

}
