#include "gpio_pin.h"

GPIOPin::GPIOPin(uint16_t pin,
                 Mode mode,
                 OType otype,
                 PushPull push_pull,
                 Speed speed)
    : mode_(mode),
      otype_(otype),
      push_pull_(push_pull),
      speed_(speed) {
    pin_number_ = lookup_pin_number_for(pin);
}

uint32_t GPIOPin::lookup_pin_number_for(uint16_t pin) {
    switch (pin) {
        case 1: return GPIO_Pin_1;
        case 2: return GPIO_Pin_2;
        case 3: return GPIO_Pin_3;
        case 4: return GPIO_Pin_4;
        case 5: return GPIO_Pin_5;
        case 6: return GPIO_Pin_6;
        case 7: return GPIO_Pin_7;
        case 8: return GPIO_Pin_8;
        case 9: return GPIO_Pin_9;
        case 10: return GPIO_Pin_10;
        case 11: return GPIO_Pin_11;
        case 12: return GPIO_Pin_12;
        case 13: return GPIO_Pin_13;
        case 14: return GPIO_Pin_14;
        case 15: return GPIO_Pin_15;
        default: return 0;
    }
}
