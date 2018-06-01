#ifndef CLOCK_UI_H_
#define CLOCK_UI_H_

#include "drivers/stm32/display_7seg.h"
#include "drivers/stm32/pec11_renc.h"
#include "drivers/stm32/rtc.h"
#include "drivers/stm32/status_led.h"

namespace clock {

class UI {
private:    
    Display7Seg* display_;
    Pec11RotaryEncoder* encoder_;
    StatusLed* status_led_;
    long knob_offset_;
    uint8_t set_position_;

    bool display_needs_refresh_;
    
    uint32_t update_count_;
    uint32_t ticks_per_half_second_;
    uint8_t last_second_;

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
       Pec11RotaryEncoder* encoder,
       StatusLed* status_led);
    ~UI() = default;

    void Clear();
    void ToggleColon(bool on);
    void SetHour(uint8_t hour, bool pm);
    void SetMinute(uint8_t minute);
    Action Update(const stm32::RTClock::Time& time);
private:
    Action set_next_position();
    Action set_change_time();
    void refresh_display();
    void toggle_status_led();
    bool is_next_second(const uint8_t current_second);
    bool is_halfway_through_second();
    bool display_needs_refresh();
};

}

#endif
