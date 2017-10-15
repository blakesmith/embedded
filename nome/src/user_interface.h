#ifndef NOME_USER_INTERFACE_H_
#define NOME_USER_INTERFACE_H_

#include "pec11_renc.h"
#include "ht16K33_display.h"
#include "status_led.h"
#include "settings.h"

namespace nome {

enum UserInterfaceRefresh {
    UI_REFRESH_NONE,
    UI_REFRESH_BPM,
    UI_REFRESH_DOWNBEAT,
    UI_REFRESH_VOLUME,
};

class Timer {
public:
    Timer(uint32_t starting_count);
    ~Timer() = default;
        
    void Tick();
    void Reset();
    void Stop();
    
    bool IsComplete() const;
private:
    const uint32_t starting_count_;
    uint32_t count_;
};
    
class UserInterface {

public:
    enum ScreenState {
        SCREEN_STATE_BPM,
        SCREEN_STATE_DOWNBEAT,
        SCREEN_STATE_VOLUME
    };

    UserInterface(Settings& settings);
    ~UserInterface() = default;
    
    void Init();
    void SetOk(bool ok);
    UserInterfaceRefresh Update();

private:
    StatusLed status_led_;
    Pec11RotaryEncoder knob_;
    HT16K33Display display_;

    long knob_offset_;
    Settings& settings_;
    size_t current_screen_position_;
    
    ScreenState current_screen_;
    Timer screen_banner_timer_;

    void refresh_display();
    UserInterfaceRefresh poll_events();
    
    UserInterfaceRefresh knob_action_for_screen(ScreenState screen, int8_t knob_offset);
    void next_screen();

    void draw_bpm();
    void draw_downbeat();
    void draw_volume();

    void tick_screen_timer();
    void start_screen_timer();
    void stop_screen_timer();
    bool showing_banner() const;
};
    
}

#endif
