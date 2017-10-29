#ifndef I2C_BUS_H_
#define I2C_BUS_H_

#include <cstddef>

#include "stm32f4xx_i2c.h"
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

    void WriteTransmitStart(uint8_t device_address);
    void WriteTransmitStop();

    void WriteReceiveStart(uint8_t device_address);
    void WriteReceiveStop();

    void WriteRaw(uint8_t data);
    
    void WriteRaw(uint16_t* data,
                  size_t size);

    void WriteRaw(uint8_t* data,
                  size_t size);
    uint8_t ReceiveData();
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
