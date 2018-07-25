#include "dip_switch.h"

namespace stm32 {

DipSwitch::DipSwitch(GPIOPin* pins, const uint8_t pin_count)
    : pins_(pins),
      pin_count_(pin_count) { }

void DipSwitch::Init() {
    for (unsigned int i = 0; i < pin_count_; i++) {
        GPIOPin& pin = pins_[i];

        pin.set_mode(GPIOPin::Mode::IN);
        pin.set_pupd(GPIOPin::PuPd::UP);
        pin.set_output(GPIOPin::OType::PUSH_PULL);
        pin.set_speed(GPIOPin::Speed::TWO_MHZ);

        pin.Init();
    }
}

uint16_t DipSwitch::Read() {
    uint16_t result = 0;

    for (unsigned int i = 0; i < pin_count_; i++) {
        GPIOPin& pin = pins_[i];
        bool state = !pin.Read();
        uint16_t bit = state ? 1 : 0;
        result |= bit << i;
    }

    return result;
}

}
