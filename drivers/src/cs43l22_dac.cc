#include "cs43l22_dac.h"

#include "stm32f4xx_gpio.h"
#include "i2c_common.h"

static constexpr I2C_TypeDef *I2Cx = I2C1;
static constexpr GPIO_TypeDef *GPIOx = GPIOB;

static constexpr uint32_t RCC_I2C_PERIPH = RCC_APB1Periph_I2C1;
static constexpr uint32_t RCC_GPIO_PERIPH = RCC_AHB1Periph_GPIOB;

static constexpr uint16_t GPIO_PS_SCL = GPIO_PinSource6;
static constexpr uint16_t GPIO_PS_SDA = GPIO_PinSource9;
static constexpr uint16_t GPIO_PIN_SCL = GPIO_Pin_6;
static constexpr uint16_t GPIO_PIN_SDA = GPIO_Pin_9;

static constexpr uint8_t GPIO_AFx = GPIO_AF_I2C1;

void CS43L22Dac::Init(uint8_t volume) {
    init_gpio();
    init_i2c();
    init_i2s();
    
    // Hold power off
    write_register(CS_REG_POW_CTL1, 0x01);
    
    // Set the output device to auto detect, headphone or speaker depending on if the headphones are plugged in
    write_register(CS_REG_POW_CTL2, CS_OUT_AUTO);

    // Configure the clocking control to AUTO, and enable MCLKDIV2
    write_register(CS_REG_CLOCKING_CTL, CS_CLOCKING_AUTO);

    // Serial port master / slave (slave), Serial clock polarity (not inverted), DSP Mode disabled, DAC interface format (I2C)
    write_register(CS_REG_INTERFACE_CTL1, 0x04);

    // Set volume the master volume
    set_volume(volume);
    
    // Set speaker mono mode
    write_register(CS_REG_PLAYBACK_CTL2, 0x06);
    
    // Set speaker attenuation level
    write_register(CS_REG_SPEAKER_A_VOL, 0x00);
    write_register(CS_REG_SPEAKER_B_VOL, 0x00);
    
    // Disable analog soft ramp
    write_register(CS_REG_ANALOG_SR, 0x00);
    
    // Disable digital soft ramp
    write_register(CS_REG_MISC_CTL, 0x04);
    
    // Disable limiter attack level
    write_register(CS_REG_LIMIT_CTL1, 0x00);
    
    // Adjust bass and trebel levels
    write_register(CS_REG_TONE_CTL, 0x0F);
    
    // Adjust PCM volume level
    write_register(CS_REG_PCMA_VOL, 0x0A);
    write_register(CS_REG_PCMB_VOL, 0x0A);
}

void CS43L22Dac::init_gpio() {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_GPIO_PERIPH, ENABLE);

    GPIO_PinAFConfig(GPIOx, GPIO_PS_SCL, GPIO_AFx);
    GPIO_PinAFConfig(GPIOx, GPIO_PS_SDA, GPIO_AFx);

    // I2C
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SCL | GPIO_PIN_SDA;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void CS43L22Dac::init_i2c() {
    I2C_InitTypeDef I2C_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_I2C_PERIPH, ENABLE);

    I2C_StructInit(&I2C_InitStructure);
    I2C_DeInit(I2Cx);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_InitStructure.I2C_OwnAddress1 = 0x36;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    
    I2C_Init(I2Cx, &I2C_InitStructure);
    I2C_Cmd(I2Cx, ENABLE);
}

void CS43L22Dac::init_i2s() {
    // TODO: Implement.
}

// Adjust and set the volume, 0 - 255.
void CS43L22Dac::set_volume(uint8_t volume) {
    uint8_t converted_volume;
    
    // Master volume from the datasheet:
    // 0 = -102db
    // 230 = 0db
    // 24 = +12db
    if (volume > 230) {
        converted_volume = volume - 231;
    } else {
        converted_volume = volume + 25;
    }

    write_register(CS_REG_MASTER_A_VOL, converted_volume);
    write_register(CS_REG_MASTER_B_VOL, converted_volume);
}

void CS43L22Dac::write_register(uint8_t reg, uint8_t value) {
}

