#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

#include "stm32f4xx_gpio.h"

class GPIOPin {
public:
    enum class Mode {
        IN,
        OUT,
        NONE
    };

    enum class OType {
        PUSH_PULL,
        OPEN_DRAIN,
        NONE
    };

    enum class PuPd {
        UP,
        DOWN,
        NONE
    };

    enum class Speed {
        TWO_MHZ,
        FIFTY_MHZ,
        NONE
    };

    GPIOPin(GPIO_TypeDef* gpiox,
            uint16_t pin);
    
    ~GPIOPin() = default;

    void Set(bool on);
    void Toggle();
    
    void Init();
    
    void set_mode(Mode mode);
    void set_output(OType otype);
    void set_pupd(PuPd pupd);
    void set_speed(Speed speed);

private:
    uint32_t pin_number_;
    GPIO_TypeDef* gpiox_;

    Mode mode_;
    OType otype_;
    PuPd pupd_;
    Speed speed_;
    
    uint32_t lookup_pin_number_for(uint16_t pin_number);
    GPIOMode_TypeDef lookup_mode_for(Mode mode);
    GPIOOType_TypeDef lookup_output_for(OType otype);
    GPIOPuPd_TypeDef lookup_push_pull_for(PuPd pupd);
    GPIOSpeed_TypeDef lookup_speed_for(Speed speed);
};

#endif
