#ifndef NOME_USER_INTERFACE_H_
#define NOME_USER_INTERFACE_H_

#include "beat.h"
#include "pinout.h"

#include "drivers/stm32/pec11_renc.h"

#ifdef TARGET_BREADBOARD
#include "drivers/stm32/ht16K33_display.h"
#else
#include "drivers/stm32/as1115_display.h"
#endif

#include "drivers/stm32/status_led.h"
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
        SCREEN_STATE_SLEEP,
        SCREEN_STATE_BPM,
        SCREEN_STATE_DOWNBEAT,
        SCREEN_STATE_VOLUME
    };

    UserInterface(Settings& settings,
                  Pinout& pinout,
                  const BeatMonitor& beat_monitor);
    ~UserInterface() = default;
    
    void Init();
    void SetOk(bool ok);
    UserInterfaceRefresh Update();

private:
    StatusLed status_led_;
    Pec11RotaryEncoder knob_;
#ifdef TARGET_BREADBOARD
    HT16K33Display display_;
#else
    AS1115Display display_;
#endif

    Settings& settings_;
    const BeatMonitor& beat_monitor_;

    long knob_offset_;
    size_t current_screen_position_;
    
    ScreenState current_screen_;
    Timer screen_banner_timer_;
    Timer user_input_timeout_;

    void refresh_display();
    UserInterfaceRefresh poll_events();
    
    UserInterfaceRefresh knob_action_for_screen(ScreenState screen, int8_t knob_offset);
    void next_screen();
    bool screen_is_sleeping() const;
    void enable_sleep_screen();
    void disable_sleep_screen();

    void draw_bpm();
    void draw_downbeat();
    void draw_volume();
    void draw_sleep_screen();

    void tick_screen_timer();
    void start_screen_timer();
    void stop_screen_timer();
    bool showing_banner() const;
};
    
}

#endif
