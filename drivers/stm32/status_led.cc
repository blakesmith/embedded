#include "drivers/stm32/status_led.h"

StatusLed::StatusLed(GPIOPin& led_ok,
                     GPIOPin& led_error)
    : led_ok_(led_ok),
      led_error_(led_error)
{}

void StatusLed::Init() {
    led_ok_.set_mode(GPIOPin::Mode::OUT);
    led_ok_.set_output(GPIOPin::OType::PUSH_PULL);
    led_ok_.set_pupd(GPIOPin::PuPd::DOWN);
    led_ok_.set_speed(GPIOPin::Speed::TWO_MHZ);

    led_error_.set_mode(GPIOPin::Mode::OUT);
    led_error_.set_output(GPIOPin::OType::PUSH_PULL);
    led_error_.set_pupd(GPIOPin::PuPd::DOWN);
    led_error_.set_speed(GPIOPin::Speed::TWO_MHZ);
    
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
