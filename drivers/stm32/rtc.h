#ifndef RTC_H_
#define RTC_H_

#include <cstdint>

namespace stm32 {

class RTClock {
public:
    enum class AM_PM {
        AM,
        PM
    };
    
    struct Time {
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        AM_PM am_pm;
    };
    
    RTClock() = default;
    ~RTClock() = default;

    void SetTime(Time* time);
    void GetTime(Time* time);
    
    void Init();
};

}

#endif
