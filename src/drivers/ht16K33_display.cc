#include "ht16K33_display.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"

// Default address. This is 224 << 1
static const uint8_t DEFAULT_DEVICE_ADDRESS = 0x70;

static const uint8_t HT16K33_BLINK_CMD = 0x80;
static const uint8_t HT16K33_BLINK_OFF = 0;
static const uint8_t HT16K33_BLINK_ON = 1;

static const uint8_t HT16K33_CMD_BRIGHTNESS = 0xE0;

HT16K33Display::HT16K33Display(uint8_t device_address)
    : device_address_(device_address) { }

HT16K33Display::HT16K33Display()
    : device_address_(DEFAULT_DEVICE_ADDRESS) { }

void HT16K33Display::Init() {
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,  ENABLE);

//    GPIOB->BSRRL = BIT_6 | BIT_7;                            // SDA, SCL -> hi
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7; // SDA, SCL def
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            // alternate function
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);  // PB6:I2C1_SCL
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);  // PB7:I2C1_SDA

    I2C_InitStructure.I2C_ClockSpeed      = 100000;
    I2C_InitStructure.I2C_Mode            = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle       = I2C_DutyCycle_16_9;
    I2C_InitStructure.I2C_OwnAddress1      = 0;
    I2C_InitStructure.I2C_Ack             = I2C_Ack_Disable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);
    
    enable_oscillator();
    SetBlinkRate(HT16K33_BLINK_OFF);
    SetBrightness(15);
}

void HT16K33Display::SetBrightness(uint8_t brightness) {
    if (brightness > 15) {
        brightness = 15;
    }
    write_start();
    write_raw(HT16K33_CMD_BRIGHTNESS | brightness);
    write_stop();
}

void HT16K33Display::SetBlinkRate(uint8_t rate) {
    if (rate > 3) {
        rate = 0;
    }
    write_start();
    write_raw(HT16K33_BLINK_CMD | HT16K33_BLINK_ON | (rate << 1));
    write_stop();
}

void HT16K33Display::ToggleColon(bool on) {
    if (on) {
        display_buffer_[2] = 0x2;
    } else {
        display_buffer_[2] = 0;
    }
}

void HT16K33Display::WriteDisplay() {
    write_start();
    write_raw(display_buffer_, 4);
    write_stop();
}

void HT16K33Display::enable_oscillator() {
    write_start();
    write_raw(0x21);
    write_stop();
}

void HT16K33Display::write_start() {
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, device_address_, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
}

void HT16K33Display::write_stop() {
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1, ENABLE);
}

void HT16K33Display::write_raw(uint16_t* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        I2C_SendData(I2C1, data[i] & 0xFF);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
        I2C_SendData(I2C1, data[i] >> 8);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    }
}

void HT16K33Display::write_raw(uint8_t data) {
    write_raw(&data, 1);
}

void HT16K33Display::write_raw(uint8_t* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        I2C_SendData(I2C1, data[i]);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    }
}
