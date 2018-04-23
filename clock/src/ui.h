#ifndef CLOCK_UI_H_
#define CLOCK_UI_H_

#include "drivers/stm32/display_7seg.h"

namespace clock {

class UI {
    Display7Seg* display_;
public:
    UI(Display7Seg* display);
    ~UI() = default;

    void Clear();
    void ToggleColon(bool on);
    void SetHour(uint8_t hour);
    void SetMinute(uint8_t minute);
    void Update();
};

}

#endif
