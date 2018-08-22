#include "drivers/stm32/status_led.h"

StatusLed::StatusLed(GPIOPin& led_ok,
                     GPIOPin& led_error)
    : led_ok_(led_ok),
      led_error_(led_error)
{}

void StatusLed::Init() {
    led_ok_.Init();
    led_error_.Init();
}

void StatusLed::SetOk(bool on) {
    led_ok_.Set(on);
}

void StatusLed::SetError(bool on) {
    led_error_.Set(on);
}

void StatusLed::ToggleOk() {
    led_ok_.Toggle();
}

void StatusLed::ToggleError() {
    led_error_.Toggle();
}
