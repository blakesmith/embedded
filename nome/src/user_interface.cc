#include "user_interface.h"

namespace nome {

UserInterface::UserInterface(Settings& settings)
    : knob_offset_(0),
      settings_(settings) { }

void UserInterface::Init() {
    status_led_.Init();
    knob_.Init();
    display_.Init();
}

void UserInterface::refresh_display() {
    display_.Clear();
    display_.SetNumber(settings_.current_bpm);
    display_.WriteDisplay();
}

UserInterfaceRefresh UserInterface::poll_events() {
    knob_.ReadState();
    if (knob_.GetButtonAction() == BUTTON_ACTION_UP) {
        knob_.ResetCount();
        return UI_REFRESH_BPM;
    }
    if (knob_offset_ != knob_.GetCount()) {
        settings_.current_bpm += knob_.GetCount() - knob_offset_;
        knob_offset_ = knob_.GetCount();
        return UI_REFRESH_BPM;
    }

    return UI_REFRESH_NONE;
}

UserInterfaceRefresh UserInterface::Update() {
    refresh_display();
    return poll_events();
}

void UserInterface::SetOk(bool ok) {
    status_led_.SetOk(ok);
}

}
