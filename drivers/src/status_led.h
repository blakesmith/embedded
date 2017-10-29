#ifndef STATUS_LED_H_
#define STATUS_LED_H_

#include "gpio_pin.h"

class StatusLed {
public:
    StatusLed(GPIOPin& led_ok,
              GPIOPin& led_error,
              GPIOPin& led_activity);
    void Init();
    void ToggleOk();
    void ToggleError();
    void ToggleActivity();
    void SetOk(bool on);
    void SetError(bool on);
    void SetActivity(bool on);
    
private:
    GPIOPin& led_ok_;
    GPIOPin& led_error_;
    GPIOPin& led_activity_;
};

#endif
