#ifndef PINOUT_H_
#define PINOUT_H_

#include "gpio_pin.h"
#include "i2c_bus.h"

struct Pinout {
    GPIOBus gpioa;
    GPIOBus gpioc;
    GPIOBus gpiod;

    // StatusLed
    GPIOPin led_ok;
    GPIOPin led_error;
    GPIOPin led_activity;

    // I2C
    GPIOPin i2c_scl;
    GPIOPin i2c_sda;
    I2CBus i2c_bus;

    Pinout();
    void Init();
};

#endif
