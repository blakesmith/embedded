#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/i2c_bus.h"
#include "drivers/stm32/rtc.h"
#include "drivers/stm32/as1115_display.h"
#include "drivers/stm32/status_led.h"

stm32::RTClock rtc;

GPIOBus gpiob(GPIOBus::Id::B);
GPIOBus gpiod(GPIOBus::Id::D);
GPIOPin scl_pin(gpiob, 6);
GPIOPin sda_pin(gpiob, 9);

I2CBus i2c(I2CBus::Id::ONE, scl_pin, sda_pin);
AS1115Display display(i2c, 5);

GPIOPin ok_led(gpiod, 15);
GPIOPin error_led(gpiod, 14);
GPIOPin activity_led(gpiod, 13);

StatusLed status_led(ok_led, error_led, activity_led);

static void set_time() {
    stm32::RTClock::Time time;

    time.hour = 12;
    time.minute = 0;
    time.second = 0;
    time.am_pm = stm32::RTClock::AM_PM::AM;
    rtc.SetTime(&time);
}

static void Init() {
    rtc.Init();
    gpiob.Init();
    gpiod.Init();
    status_led.Init();
    i2c.Init();
    display.Init();

    set_time();
}

static void update_time() {
    stm32::RTClock::Time time;

    rtc.GetTime(&time);
    display.SetNumber(0, time.hour, false);
    display.SetNumber(3, time.minute, true);
    display.WriteDisplay();
}

static void delay() {
    for (int i = 0; i < 1280000; i++);
}

int main() {
    Init();

    status_led.SetOk(true);
    while (true) {
        update_time();
        delay();
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}
