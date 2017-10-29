#include "i2c_bus.h"

I2CBus::I2CBus(Id id,
               GPIOPin& scl_pin,
               GPIOPin& sda_pin)
    : id_(id),
      scl_pin_(scl_pin),
      sda_pin_(sda_pin) {
    i2cx_ = lookup_i2cx_for(id);
}

void I2CBus::Init() {
    I2C_InitTypeDef i2c_init;

    RCC_APB1PeriphClockCmd(lookup_clock_for(id_), ENABLE);
    
    scl_pin_.set_mode(GPIOPin::Mode::AF);
    scl_pin_.set_output(GPIOPin::OType::OPEN_DRAIN);
    scl_pin_.set_pupd(GPIOPin::PuPd::NONE);
    scl_pin_.set_speed(GPIOPin::Speed::TWO_MHZ);
    scl_pin_.set_alternative_function(lookup_alternative_function_for(id_));

    sda_pin_.set_mode(GPIOPin::Mode::AF);
    sda_pin_.set_output(GPIOPin::OType::OPEN_DRAIN);
    sda_pin_.set_pupd(GPIOPin::PuPd::NONE);
    sda_pin_.set_speed(GPIOPin::Speed::TWO_MHZ);
    sda_pin_.set_alternative_function(lookup_alternative_function_for(id_));

    I2C_StructInit(&i2c_init);
    I2C_DeInit(i2cx_);
    i2c_init.I2C_Mode = I2C_Mode_I2C;
    i2c_init.I2C_ClockSpeed = 100000;
    i2c_init.I2C_OwnAddress1 = 0x35;
    i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
    i2c_init.I2C_Ack = I2C_Ack_Enable;
    i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    
    I2C_Init(i2cx_, &i2c_init);
    I2C_Cmd(i2cx_, ENABLE);
}

uint32_t I2CBus::lookup_clock_for(Id id) {
    switch (id) {
        case Id::ONE: return RCC_APB1Periph_I2C1;
        case Id::TWO: return RCC_APB1Periph_I2C2;
        case Id::THREE: return RCC_APB1Periph_I2C3;
        default: return 0;
    }
}

GPIOPin::Af I2CBus::lookup_alternative_function_for(Id id) {
    switch (id) {
        case Id::ONE: return GPIOPin::Af::I2C_1;
        case Id::TWO: return GPIOPin::Af::I2C_2;
        case Id::THREE: return GPIOPin::Af::I2C_3;
        default: return GPIOPin::Af::NONE;
    }
}

I2C_TypeDef* I2CBus::lookup_i2cx_for(Id id) {
    switch (id) {
        case Id::ONE: return I2C1;
        case Id::TWO: return I2C2;
        case Id::THREE: return I2C3;
        default: return nullptr;
    }
}
