#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

#include "stm32f4xx_gpio.h"

#include "gpio_bus.h"

class GPIOPin {
public:
    enum class Mode {
        AF,
        IN,
        OUT,
        NONE
    };

    enum class Af {
        I2C_1,
        I2C_2,
        I2C_3,
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

    GPIOPin(GPIOBus& bus,
            uint16_t pin);
    
    ~GPIOPin() = default;

    void Set(bool on);
    void Toggle();
    uint8_t Read();
    
    void Init();
    
    void set_mode(Mode mode);
    void set_output(OType otype);
    void set_pupd(PuPd pupd);
    void set_speed(Speed speed);
    void set_alternative_function(Af af);
    GPIOBus& get_bus();
    uint32_t get_pin_number();

private:
    uint32_t pin_number_;
    uint16_t pin_source_;
    GPIOBus& bus_;

    Mode mode_;
    OType otype_;
    PuPd pupd_;
    Speed speed_;
    Af af_;

    uint16_t lookup_pin_source_for(uint16_t pin_number);
    uint32_t lookup_pin_number_for(uint16_t pin_number);
    uint8_t lookup_alternative_function_for(Af af);
    GPIOMode_TypeDef lookup_mode_for(Mode mode);
    GPIOOType_TypeDef lookup_output_for(OType otype);
    GPIOPuPd_TypeDef lookup_push_pull_for(PuPd pupd);
    GPIOSpeed_TypeDef lookup_speed_for(Speed speed);
};

#endif
