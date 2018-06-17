#include "ui.h"

namespace clock {

UI::UI(Display7Seg* display,
       Pec11RotaryEncoder* encoder,
       StatusLed* status_led)
    : display_(display),
      encoder_(encoder),
      status_led_(status_led),
      knob_offset_(0),
      set_position_(3),
      display_needs_refresh_(true),
      update_count_(0),
      ticks_per_half_second_(4096), // Set something reasonably high for initialization
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
    display_needs_refresh_ = true;
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
    display_needs_refresh_ = false;
}

void UI::toggle_status_led() {
    // TODO: Rip out once LED order is switched
    status_led_->ToggleError();
}

bool UI::is_next_second(const uint8_t current_second) {
    return last_second_ != current_second;
}

bool UI::is_halfway_through_second(const stm32::RTClock::Time& time) {
    return update_count_ == ticks_per_half_second_;
}

bool UI::display_needs_refresh() {
    return display_needs_refresh_;
}

UI::Action UI::Update(const stm32::RTClock::Time& time) {
    if (is_next_second(time.second)) {
        last_second_ = time.second;
        ticks_per_half_second_ = update_count_ / 2; // Half second per colon tick
        update_count_ = 0;
        display_needs_refresh_ = true;
    }
    encoder_->ReadState();
    if (encoder_->GetButtonAction() == BUTTON_ACTION_DOWN) {
        refresh_display();
        return set_next_position();
    }
    if (knob_offset_ != encoder_->GetCount()) {
        return set_change_time();
    }
    if (is_halfway_through_second(time) || display_needs_refresh()) {
        refresh_display();
        toggle_status_led();
    }
    update_count_++;
    return Action(0, 0);
}

}
