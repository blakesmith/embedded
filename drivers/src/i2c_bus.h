#ifndef I2C_BUS_H_
#define I2C_BUS_H_

#include "gpio_pin.h"

class I2CBus {
public:
    enum class Id {
        ONE,
        TWO,
        THREE
    };

    I2CBus(Id id,
           GPIOPin& scl_pin,
           GPIOPin& sda_pin);

    void Init();

private:
    Id id_;
    I2C_TypeDef* i2cx_;
    GPIOPin& scl_pin_;
    GPIOPin& sda_pin_;

    I2C_TypeDef* lookup_i2cx_for(Id id);
    uint32_t lookup_clock_for(Id id);
    GPIOPin::Af lookup_alternative_function_for(Id id);
};

#endif
