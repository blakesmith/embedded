#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/i2c_bus.h"
#include "drivers/stm32/rtc.h"
#include "drivers/stm32/ht16K33_display.h"

stm32::RTClock rtc;

GPIOBus gpio(GPIOBus::Id::B);
GPIOPin scl_pin(gpio, 6);
GPIOPin sda_pin(gpio, 7);
I2CBus i2c(I2CBus::Id::ONE, scl_pin, sda_pin);
HT16K33Display display(i2c, 5);

void Init() {
    rtc.Init();
    gpio.Init();
    i2c.Init();
    display.Init();
}

void display_test() {
    display.SetNumber(1234);
    display.WriteDisplay();
}

int main() {
    Init();
    display_test();
    
    while (true) {
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}
