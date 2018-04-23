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

void UI::SetHour(uint8_t hour, bool pm) {
    display_->SetNumber(0, hour, 2, false);
    display_->ToggleAmPm(pm);
}

void UI::SetMinute(uint8_t minute) {
    display_->SetNumber(3, minute, 2, true);
}

UI::Action UI::set_next_position() {
    set_position_ = (set_position_ + 1) % 4;
    return Action(0, 0);
}

UI::Action UI::set_change_time() {
    update_count_ = 0;
    int8_t diff = encoder_->GetCount() - knob_offset_;
    knob_offset_ = encoder_->GetCount();
    switch (set_position_) {
        case 0:
            return Action(diff, 0);
        case 2:
            return Action(0, diff);
        default:
            return Action(0, 0);
    }
}

void UI::refresh_display() {
    if (set_position_ != 3) {
        display_->SetSegment(set_position_ * 2, 0, false, true);
    }
    display_->ToggleColon(colon_toggle_);
    colon_toggle_ = !colon_toggle_;
    display_->WriteDisplay();
}

UI::Action UI::Update() {
    encoder_->ReadState();
    if (encoder_->GetButtonAction() == BUTTON_ACTION_DOWN) {
        return set_next_position();
    }
    if (knob_offset_ != encoder_->GetCount()) {
        return set_change_time();
    }
    if (update_count_ == 0) {
        refresh_display();
    }
    update_count_ = (update_count_ + 1) % 9000;
    return Action(0, 0);
}

}
