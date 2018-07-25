#ifndef DIP_SWITCH_H_
#define DIP_SWITCH_H_

#include "gpio_pin.h"

namespace stm32 {

class DipSwitch {
public:
    DipSwitch(GPIOPin* pins,
              const uint8_t pin_count);
    ~DipSwitch() = default;

    void Init();
    uint16_t Read();

private:
    GPIOPin* pins_;
    const uint8_t pin_count_;
};

}

#endif
