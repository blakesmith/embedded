#ifndef STATUS_LED_H_
#define STATUS_LED_H_

#include "gpio_pin.h"

class StatusLed {
public:
    StatusLed(GPIOPin& led_ok,
              GPIOPin& led_error);
    void Init();
    void ToggleOk();
    void ToggleError();
    void SetOk(bool on);
    void SetError(bool on);
    
private:
    GPIOPin& led_ok_;
    GPIOPin& led_error_;
};

#endif
