#include <stm32f4xx.h>
#include <cstddef>

#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/i2c_bus.h"
//#include "drivers/stm32/ht16K33_display.h"
#include "drivers/stm32/as1115_display.h"
#include "drivers/stm32/status_led.h"

GPIOBus gpiob(GPIOBus::Id::B);
GPIOBus gpiod(GPIOBus::Id::D);

GPIOPin scl_pin(gpiob, 6);
GPIOPin sda_pin(gpiob, 9);

GPIOPin ok_led(gpiod, 15);
GPIOPin error_led(gpiod, 14);
GPIOPin activity_led(gpiod, 13);

I2CBus i2c(I2CBus::Id::ONE, scl_pin, sda_pin);
//HT16K33Display display(i2c, 5);
AS1115Display display(i2c, 5);

StatusLed status_led(ok_led, error_led, activity_led);

volatile uint32_t count = 0;

void Init() {
    gpiob.Init();
    gpiod.Init();

    status_led.Init();
    i2c.Init();
    display.Init();
}

void UpdateDisplay() {
    display.Clear();
    display.ToggleColon(true);
//    display.SetNumber(count);
    display.WriteDisplay();
}

int main() {
    Init();

    status_led.SetOk(true);
    while (true) {
        UpdateDisplay();
        for (int i = 0; i < 128000; i++);
        count++;
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}
