#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/i2c_bus.h"
#include "drivers/stm32/rtc.h"
#include "drivers/stm32/as1115_display.h"
#include "drivers/stm32/status_led.h"
#include "drivers/stm32/pec11_renc.h"

#include "ui.h"

using namespace clock;
using namespace stm32;

RTClock rtc(RTClock::ClockSource::LSE);

GPIOBus gpioa(GPIOBus::Id::A);
GPIOBus gpiob(GPIOBus::Id::B);

GPIOPin scl_pin(gpiob, 6);
GPIOPin sda_pin(gpiob, 9);

I2CBus i2c(I2CBus::Id::ONE, scl_pin, sda_pin);
AS1115Display display(i2c, 5);

GPIOPin ok_led(gpioa, 5);
GPIOPin error_led(gpioa, 6);

StatusLed status_led(ok_led, error_led);

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
    i2c.Init();
    display.Init();
    encoder.Init();
    status_led.SetError(!rtc.Init());
    status_led.SetError(!set_time());
}

static void set_hour(RTClock::Time* time, int8_t hour_diff) {
    int8_t hour_register = time->hour + hour_diff;
    if (hour_register > 12) {
        hour_register = 1;
    } else if (hour_register < 1) {
        hour_register = 12;
    }

    time->hour = hour_register;

    if (hour_register == 12) {
        time->am_pm = time->am_pm == RTClock::AM_PM::AM ?
            RTClock::AM_PM::PM :
            RTClock::AM_PM::AM;
    }
}

static void set_minute(RTClock::Time* time, int8_t minute_diff) {
    int8_t minute_register = time->minute + minute_diff;
    if (minute_register > 59) {
        minute_register = 0;
    } else if (minute_register < 0) {
        minute_register = 59;
    }

    time->minute = minute_register;
}

static void update_time() {
    RTClock::Time time;

    rtc.GetTime(&time);
    ui.Clear();
    ui.SetHour(time.hour, time.am_pm == RTClock::AM_PM::PM);
    ui.SetMinute(time.minute);
    UI::Action action = ui.Update(time);
    if (action.NeedsUpdate()) {
        if (action.hour_diff != 0) {
            set_hour(&time, action.hour_diff);
        }
        
        if (action.minute_diff != 0) {
            set_minute(&time, action.minute_diff);
        }

        status_led.SetError(!rtc.SetTime(&time));
    }
}

int main() {
    Init();

    status_led.SetOk(true);
    for (unsigned int i = 0; i < 320000; i++);
    while (true) {
        update_time();
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}
