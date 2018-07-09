#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

#include "gpio_bus.h"

class GPIOPin {
public:
    enum class Mode {
        AF,
        IN,
        OUT,
        NONE
    };

    enum Af {
        I2C_1,
        I2C_2,
        I2C_3,
        I2C_4,
        I2C_5,
        I2C_5_2,
        SPI_0,
        SPI_0_2,
        SPI_1,
        SPI_2,
        SPI_3,
        SPI_5_2,
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
    bool Read();
    
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

    uint32_t lookup_pin_number_for(uint16_t pin_number);
    uint16_t lookup_pin_source_for(uint16_t pin_number);

#if defined(STM32_STD_PERIPH)
    // Standard peripheral init
    void std_periph_init();
    uint8_t lookup_alternative_function_for(Af af);
    GPIOMode_TypeDef lookup_mode_for(Mode mode);
    GPIOOType_TypeDef lookup_output_for(OType otype);
    GPIOPuPd_TypeDef lookup_push_pull_for(PuPd pupd);
    GPIOSpeed_TypeDef lookup_speed_for(Speed speed);
#endif

#ifdef STM32_HAL
    // Hal init function
    void hal_init();
    uint8_t hal_lookup_alternative_function_for(Af af);
    uint32_t hal_lookup_mode_output_for(Mode mode, OType otype);
    uint32_t hal_lookup_push_pull_for(PuPd pupd);
    uint32_t hal_lookup_speed_for(Speed speed);
#endif
};

#endif
