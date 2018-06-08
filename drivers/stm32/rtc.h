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
        uint32_t subsecond;
        AM_PM am_pm;
    };
    
    RTClock() = default;
    ~RTClock() = default;

    bool SetTime(Time* time);
    void GetTime(Time* time);
    
    bool Init();
};

}

#endif
