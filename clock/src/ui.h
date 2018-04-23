#ifndef CLOCK_UI_H_
#define CLOCK_UI_H_

#include "drivers/stm32/display_7seg.h"
#include "drivers/stm32/pec11_renc.h"

namespace clock {

class UI {
private:    
    Display7Seg* display_;
    Pec11RotaryEncoder* encoder_;
    long knob_offset_;
    uint8_t set_position_;
    uint32_t update_count_;
    bool colon_toggle_;

public:

    struct Action {
        int8_t hour_diff;
        int8_t minute_diff;

        Action(int8_t h, int8_t m)
            : hour_diff(h),
              minute_diff(m) { }

        bool NeedsUpdate() {
            return hour_diff != 0 || minute_diff != 0;
        }
    };

    UI(Display7Seg* display,
       Pec11RotaryEncoder* encoder_);
    ~UI() = default;

    void Clear();
    void ToggleColon(bool on);
    void SetHour(uint8_t hour);
    void SetMinute(uint8_t minute);
    Action Update();
private:
    Action set_next_position();
    Action set_change_time();
    void refresh_display();
};

}

#endif
