#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

#include "stm32f4xx_gpio.h"

class GPIOPin {
public:
    enum class Mode {
        IN,
        OUT
    };

    enum class OType {
        PUSH_PULL,
        OPEN_DRAIN
    };

    enum class PushPull {
        UP,
        DOWN
    };

    enum Speed {
        TWO_MHZ,
        FIFTY_MHZ
    };

    GPIOPin(uint16_t pin,
            Mode mode,
            OType otype,
            PushPull push_pull,
            Speed speed);
    
    ~GPIOPin() = default;

    void PopulateInit(GPIO_InitTypeDef* gpio_init);

private:
    uint32_t pin_number_;
    Mode mode_;
    OType otype_;
    PushPull push_pull_;
    Speed speed_;
    
    uint32_t lookup_pin_number_for(uint16_t pin_number);
    GPIOMode_TypeDef lookup_mode_for(Mode mode);
    GPIOOType_TypeDef lookup_output_for(OType otype);
    GPIOPuPd_TypeDef lookup_push_pull_for(PushPull push_pull);
};

#endif
