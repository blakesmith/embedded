#ifndef LED_H_
#define LED_H_

#include "gpio_pin.h"

class LED {
public:
    LED(GPIOPin& pin);
    ~LED() = default;

    void Init();
    void Toggle();
    void Set(bool on);
    void Enable();
    void Disable();

private:
    GPIOPin& pin_;
};

#endif
