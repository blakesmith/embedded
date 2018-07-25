#include "dip_switch.h"

namespace stm32 {

DipSwitch::DipSwitch(GPIOPin* pins, const uint8_t pin_count)
    : pins_(pins),
      pin_count_(pin_count) { }

void DipSwitch::Init() {
}

uint16_t DipSwitch::Read() {
    return 0;
}

}
