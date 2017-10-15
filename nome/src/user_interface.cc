#include "user_interface.h"

namespace nome {

static const UserInterface::ScreenState ALL_SCREENS[] = {
    UserInterface::ScreenState::SCREEN_STATE_BPM,
    UserInterface::ScreenState::SCREEN_STATE_DOWNBEAT,
    UserInterface::ScreenState::SCREEN_STATE_VOLUME
};

static const size_t ALL_SCREENS_SIZE = sizeof(ALL_SCREENS) / sizeof(UserInterface::ScreenState);

UserInterface::UserInterface(Settings& settings)
    : knob_offset_(0),
      settings_(settings),
      current_screen_position_(0),
      current_screen_(ALL_SCREENS[current_screen_position_]),
      showing_banner_(true) { }

void UserInterface::Init() {
    status_led_.Init();
    knob_.Init();
    display_.Init();
}

void UserInterface::next_screen() {
    knob_offset_ = 0;
    showing_banner_ = true;
    knob_.ResetCount();
    current_screen_position_ = (current_screen_position_ + 1) % ALL_SCREENS_SIZE;
    current_screen_ = ALL_SCREENS[current_screen_position_];
}

void UserInterface::draw_bpm() {
    if (showing_banner_) {
        display_.SetChar(0, 'b');
        display_.SetChar(1, 'P');
        display_.SetChar(3, 'M');
    } else {
        display_.SetChar(0, 'b');
        display_.SetNumber(settings_.GetBPM());
    }
}

void UserInterface::draw_downbeat() {
    if (showing_banner_) {
        display_.SetChar(0, 'd');
        display_.SetChar(1, 'b');
    } else {
        display_.SetChar(0, 'd');
        display_.SetNumber(settings_.GetDownbeat());
    }
}

void UserInterface::draw_volume() {
    if (showing_banner_) {
        display_.SetChar(0, 'v');
        display_.SetChar(1, 'O');
        display_.SetChar(3, 'L');
    } else {
        display_.SetChar(0, 'v');
        display_.SetNumber(settings_.GetVolume());
    }
}

void UserInterface::refresh_display() {
    display_.Clear();
    switch (current_screen_) {
        case SCREEN_STATE_BPM: {
            draw_bpm();
            break;
        }
        case SCREEN_STATE_DOWNBEAT: {
            draw_downbeat();
            break;
        }
        case SCREEN_STATE_VOLUME: {
            draw_volume();
            break;
        }
        default:
            break;
    }
    display_.WriteDisplay();
}

UserInterfaceRefresh UserInterface::knob_action_for_screen(ScreenState screen, int8_t knob_offset) {
    switch (screen) {
        case SCREEN_STATE_BPM: {
            settings_.AddBPM(knob_offset);
            return UI_REFRESH_BPM;
        }
        case SCREEN_STATE_DOWNBEAT: {
            settings_.AddDownbeat(knob_offset);
            return UI_REFRESH_DOWNBEAT;
        }
        case SCREEN_STATE_VOLUME:
            settings_.AddVolume(knob_offset);
            return UI_REFRESH_VOLUME;
        default:
            return UI_REFRESH_NONE;
    }
}

UserInterfaceRefresh UserInterface::poll_events() {
    knob_.ReadState();
    if (knob_.GetButtonAction() == BUTTON_ACTION_DOWN) {
        next_screen();
        return UI_REFRESH_NONE;
    }
    if (knob_offset_ != knob_.GetCount()) {
        showing_banner_ = false;
        UserInterfaceRefresh refresh_action = knob_action_for_screen(current_screen_,
                                                                     static_cast<int8_t>(knob_.GetCount() - knob_offset_));
        knob_offset_ = knob_.GetCount();
        return refresh_action;
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
