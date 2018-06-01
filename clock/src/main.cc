#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/i2c_bus.h"
#include "drivers/stm32/rtc.h"
#include "drivers/stm32/as1115_display.h"
#include "drivers/stm32/status_led.h"
#include "drivers/stm32/pec11_renc.h"

#include "ui.h"

using namespace clock;
using namespace stm32;

RTClock rtc;

GPIOBus gpioa(GPIOBus::Id::A);
GPIOBus gpiob(GPIOBus::Id::B);

GPIOPin scl_pin(gpiob, 6);
GPIOPin sda_pin(gpiob, 9);

I2CBus i2c(I2CBus::Id::ONE, scl_pin, sda_pin);
AS1115Display display(i2c, 5);

GPIOPin ok_led(gpiob, 3);
GPIOPin error_led(gpiob, 4);
GPIOPin activity_led(gpiob, 5);

StatusLed status_led(ok_led, error_led, activity_led);

GPIOPin encoder_clockwise(gpioa, 1);
GPIOPin encoder_counter_clockwise(gpioa, 2);
GPIOPin encoder_button(gpioa, 3);

Pec11RotaryEncoder encoder(encoder_clockwise,
                           encoder_counter_clockwise,
                           encoder_button);

UI ui(&display, &encoder, &status_led);

static bool set_time() {
    RTClock::Time time;

    time.hour = 12;
    time.minute = 0;
    time.second = 0;
    time.am_pm = RTClock::AM_PM::AM;
    return rtc.SetTime(&time);
}

static void Init() {
    gpioa.Init();
    gpiob.Init();
    status_led.Init();
    status_led.SetError(!rtc.Init());
    i2c.Init();
    display.Init();
    encoder.Init();

    status_led.SetError(!set_time());
}

static void update_time() {
    RTClock::Time time;

    rtc.GetTime(&time);
    ui.Clear();
    ui.SetHour(time.hour, time.am_pm == RTClock::AM_PM::PM);
    ui.SetMinute(time.minute);
    UI::Action action = ui.Update(time);
    if (action.NeedsUpdate()) {
        if (action.hour_diff > 0) {
            time.hour = time.hour + action.hour_diff;
            if (time.hour == 12) {
                time.am_pm = time.am_pm == RTClock::AM_PM::AM ?
                    RTClock::AM_PM::PM :
                    RTClock::AM_PM::AM;
            }
            if (time.hour > 12) {
                time.hour = 1;
            }
        }
        if (action.minute_diff > 0) {
            time.minute = time.minute + action.minute_diff;
            if (time.minute > 59) {
                time.minute = 0;
            }
        }
        status_led.SetError(!rtc.SetTime(&time));
    }
}

int main() {
    Init();

    status_led.SetOk(true);
    while (true) {
        update_time();
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}
