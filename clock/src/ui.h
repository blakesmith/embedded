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
    
public:
    UI(Display7Seg* display,
       Pec11RotaryEncoder* encoder_);
    ~UI() = default;

    void Clear();
    void ToggleColon(bool on);
    void SetHour(uint8_t hour);
    void SetMinute(uint8_t minute);
    void Update();
};

}

#endif
