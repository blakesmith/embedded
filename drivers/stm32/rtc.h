#ifndef RTC_H_
#define RTC_H_

namespace stm32 {

class RTClock {
public:
    RTClock() = default;
    ~RTClock() = default;
    
    void Init();
};

}

#endif
