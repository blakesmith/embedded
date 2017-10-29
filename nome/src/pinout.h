#ifndef PINOUT_H_
#define PINOUT_H_

#include "gpio_pin.h"

struct Pinout {        
    GPIOBus gpiod;

    GPIOPin led_ok;
    GPIOPin led_error;
    GPIOPin led_activity;

    Pinout();
    void Init();
        
};

#endif
