#include "user_interface.h"

namespace nome {

static const UserInterface::ScreenState ALL_SCREENS[] = {
    UserInterface::ScreenState::SCREEN_STATE_BPM,
    UserInterface::ScreenState::SCREEN_STATE_DOWNBEAT
};

static const size_t ALL_SCREENS_SIZE = sizeof(ALL_SCREENS) / sizeof(UserInterface::ScreenState);

UserInterface::UserInterface(Settings& settings)
    : knob_offset_(0),
      settings_(settings),
      current_screen_position_(0),
      current_screen_(ALL_SCREENS[current_screen_position_]) { }

void UserInterface::Init() {
    status_led_.Init();
    knob_.Init();
    display_.Init();
}

void UserInterface::next_screen() {
    knob_offset_ = 0;
    knob_.ResetCount();
    current_screen_position_ = (current_screen_position_ + 1) % ALL_SCREENS_SIZE;
    current_screen_ = ALL_SCREENS[current_screen_position_];
}

void UserInterface::refresh_display() {
    switch (current_screen_) {
        case SCREEN_STATE_BPM: {
            display_.Clear();
            display_.SetNumber(settings_.current_bpm);
            display_.WriteDisplay();
            break;
        }
        case SCREEN_STATE_DOWNBEAT: {
            display_.Clear();
            display_.SetNumber(settings_.current_downbeat);
            display_.WriteDisplay();
            break;
        }
        default:
            break;
    }
}

UserInterfaceRefresh UserInterface::refresh_for_screen(ScreenState screen) {
    switch (screen) {
        case SCREEN_STATE_BPM:
            return UI_REFRESH_BPM;
        case SCREEN_STATE_DOWNBEAT:
            return UI_REFRESH_DOWNBEAT;
        case SCREEN_STATE_VOLUME:
            return UI_REFRESH_VOLUME;
        default:
            return UI_REFRESH_NONE;
    }
}

uint16_t* UserInterface::knob_value_for_screen(ScreenState screen) {
    switch (screen) {
        case SCREEN_STATE_BPM:
            return &(settings_.current_bpm);
        case SCREEN_STATE_DOWNBEAT:
            return &(settings_.current_downbeat);
        default:
            return nullptr;
    }
}

UserInterfaceRefresh UserInterface::poll_events() {
    knob_.ReadState();
    if (knob_.GetButtonAction() == BUTTON_ACTION_UP) {
        next_screen();
        return UI_REFRESH_NONE;
    }
    if (knob_offset_ != knob_.GetCount()) {
        uint16_t* knob_value = knob_value_for_screen(current_screen_);
        if (knob_value != nullptr) {
            *knob_value += knob_.GetCount() - knob_offset_;
            knob_offset_ = knob_.GetCount();
        }
        return refresh_for_screen(current_screen_);
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
