#include "led.h"

LED::LED(GPIOPin& pin)
    : pin_(pin) { }

void LED::Init() {
    pin_.set_mode(GPIOPin::Mode::OUT);
    pin_.set_output(GPIOPin::OType::PUSH_PULL);
    pin_.set_pupd(GPIOPin::PuPd::DOWN);
    pin_.set_speed(GPIOPin::Speed::TWO_MHZ);

    pin_.Init();
}

void LED::Set(bool on) {
    pin_.Set(on);
}

void LED::Toggle() {
    pin_.Toggle();
}

void LED::Enable() {
    pin_.Set(true);
}

void LED::Disable() {
    pin_.Set(false);
}
