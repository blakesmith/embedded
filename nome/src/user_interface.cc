#include "user_interface.h"

namespace nome {

static const UserInterface::ScreenState ALL_SCREENS[] = {
    UserInterface::ScreenState::SCREEN_STATE_BPM,
    UserInterface::ScreenState::SCREEN_STATE_DOWNBEAT,
    UserInterface::ScreenState::SCREEN_STATE_VOLUME
};

static constexpr uint8_t N_DIGITS = 5;
static const size_t ALL_SCREENS_SIZE = sizeof(ALL_SCREENS) / sizeof(UserInterface::ScreenState);

UserInterface::UserInterface(
    Settings& settings,
    Pinout& pinout,
    const BeatMonitor& beat_monitor)
    : status_led_(pinout.led_ok,
                  pinout.led_error,
                  pinout.led_activity),
      knob_(pinout.encoder_clockwise,
            pinout.encoder_counter_clockwise,
            pinout.encoder_button),
      display_(pinout.i2c_bus, N_DIGITS),
      settings_(settings),
      beat_monitor_(beat_monitor),
      knob_offset_(0),
      current_screen_position_(0),
      current_screen_(ALL_SCREENS[current_screen_position_]),
      screen_banner_timer_(0x400),
      user_input_timeout_(0x2000) { }

void UserInterface::Init() {
    status_led_.Init();
    knob_.Init();
    display_.Init();
}

void UserInterface::next_screen() {
    knob_offset_ = 0;
    screen_banner_timer_.Reset();
    knob_.ResetCount();
    current_screen_position_ = (current_screen_position_ + 1) % ALL_SCREENS_SIZE;
    current_screen_ = ALL_SCREENS[current_screen_position_];

}

void UserInterface::enable_sleep_screen() {
    current_screen_ = SCREEN_STATE_SLEEP;
}

void UserInterface::disable_sleep_screen() {
    screen_banner_timer_.Reset();
    current_screen_ = ALL_SCREENS[current_screen_position_];
}

bool UserInterface::screen_is_sleeping() const {
    return current_screen_ == SCREEN_STATE_SLEEP;
}

void UserInterface::draw_sleep_screen() {
    uint32_t total_beats = beat_monitor_.GetTotalBeats();
    bool colon_on = total_beats % 2 == 0;
    uint8_t dot_position = total_beats % 4;
    if (dot_position >= 2) {
        dot_position++;
    }
    display_.SetSegment(dot_position, 0, false, true);
    display_.ToggleColon(colon_on);
}

void UserInterface::draw_bpm() {
    if (showing_banner()) {
        display_.SetChar(0, 'b');
        display_.SetChar(1, 'P');
        display_.SetChar(3, 'M');
    } else {
        display_.SetChar(0, 'b');
        display_.SetNumber(settings_.GetBPM());
    }
}

void UserInterface::draw_downbeat() {
    if (showing_banner()) {
        display_.SetChar(0, 'd');
        display_.SetChar(1, 'b');
    } else {
        display_.SetChar(0, 'd');
        display_.SetNumber(settings_.GetDownbeat());
    }
}

void UserInterface::draw_volume() {
    if (showing_banner()) {
        display_.SetChar(0, 'v');
        display_.SetChar(1, 'O');
        display_.SetChar(3, 'L');
    } else {
        display_.SetChar(0, 'v');
        display_.SetNumber(settings_.GetVolume());
    }
}

void UserInterface::refresh_display() {
    if (!screen_is_sleeping() && user_input_timeout_.IsComplete()) {
        enable_sleep_screen();
    }

    display_.Clear();
    switch (current_screen_) {
        case SCREEN_STATE_SLEEP: {
            draw_sleep_screen();
            break;
        }
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
        case SCREEN_STATE_SLEEP: {
            disable_sleep_screen();
            return UI_REFRESH_NONE;
        }
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
        user_input_timeout_.Reset();
        if (screen_is_sleeping()) {
            disable_sleep_screen();
        } else {
            next_screen();
        }
        return UI_REFRESH_NONE;
    }
    if (knob_offset_ != knob_.GetCount()) {
        user_input_timeout_.Reset();
        screen_banner_timer_.Stop();
        UserInterfaceRefresh refresh_action = knob_action_for_screen(current_screen_,
                                                                     static_cast<int8_t>(knob_.GetCount() - knob_offset_));
        knob_offset_ = knob_.GetCount();
        return refresh_action;
    }

    return UI_REFRESH_NONE;
}

UserInterfaceRefresh UserInterface::Update() {
    screen_banner_timer_.Tick();
    user_input_timeout_.Tick();
    refresh_display();
    return poll_events();
}

void UserInterface::SetOk(bool ok) {
    status_led_.SetOk(ok);
}

bool UserInterface::showing_banner() const {
    return !screen_banner_timer_.IsComplete();
}

Timer::Timer(uint32_t starting_count)
    : starting_count_(starting_count) {
    Reset();
}

void Timer::Tick() {
    int32_t value = count_ - 1;
    if (value < 0) {
        count_ = 0;
    } else {
        count_ = value;
    }
}

void Timer::Stop() {
    count_ = 0;
}

void Timer::Reset() {
    count_ = starting_count_;
}

bool Timer::IsComplete() const {
    return count_ == 0;
}

}
