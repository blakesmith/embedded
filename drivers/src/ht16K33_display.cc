#include "ht16K33_display.h"

#include "stm32f4xx_gpio.h"
#include "i2c_common.h"

static constexpr I2C_TypeDef *I2Cx = I2C2;
static constexpr GPIO_TypeDef *GPIOx = GPIOB;

static constexpr uint32_t RCC_I2C_PERIPH = RCC_APB1Periph_I2C2;
static constexpr uint32_t RCC_GPIO_PERIPH = RCC_AHB1Periph_GPIOB;

static constexpr uint16_t GPIO_PS_SCL = GPIO_PinSource10;
static constexpr uint16_t GPIO_PS_SDA = GPIO_PinSource11;
static constexpr uint16_t GPIO_PIN_SCL = GPIO_Pin_10;
static constexpr uint16_t GPIO_PIN_SDA = GPIO_Pin_11;

static constexpr uint8_t GPIO_AFx = GPIO_AF_I2C2;

static const uint8_t NUMBER_TABLE[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
};

// Default address.
static const uint8_t DEFAULT_DEVICE_ADDRESS = 0x70 << 1;

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

    RCC_APB1PeriphClockCmd(RCC_I2C_PERIPH, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_GPIO_PERIPH, ENABLE);

    GPIO_PinAFConfig(GPIOx, GPIO_PS_SCL, GPIO_AFx);
    GPIO_PinAFConfig(GPIOx, GPIO_PS_SDA, GPIO_AFx);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SCL | GPIO_PIN_SDA;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    I2C_StructInit(&I2C_InitStructure);
    I2C_DeInit(I2Cx);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_InitStructure.I2C_OwnAddress1 = 0x35;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    
    I2C_Init(I2Cx, &I2C_InitStructure);
    I2C_Cmd(I2Cx, ENABLE);

    enable_oscillator();
    SetBlinkRate(HT16K33_BLINK_OFF);
    SetBrightness(15);

    Clear();
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

// Set a single number 1 - 9, in the display. Value number positions are 0, 1, 3, 4. Position 2 is the colon.
void HT16K33Display::SetNumber(uint8_t pos, uint8_t number, bool dot) {
    if (pos > 4 || pos == 2) {
        pos = 0;
    }
    if (number > 9) {
        number = 0;
    }
    uint8_t value = NUMBER_TABLE[number] | (dot << 7);
    display_buffer_[pos] = value;
}

// Set a specific segment within a position. Segments are 0 - 7. Segment 7 is the dot to the right of the digit.
// Segment 0 is the top-most LED, other segments move clockwise around the digit, with Segment 6 being the middle
// LED (Think: The middle bar on an 8). See a picture here: https://www.adafruit.com/product/880 ... Segment 0 = A.
void HT16K33Display::SetSegment(uint8_t pos, uint8_t segment, bool on, bool dot) {
    if (pos > 4 || pos == 2) {
        pos = 0;
    }
    if (segment > 6) {
        segment = 0;
    }
    uint8_t value = (on << segment) | (dot << 7);
    display_buffer_[pos] = value;
}

void HT16K33Display::ToggleColon(bool on) {
    if (on) {
        display_buffer_[2] = 0x2;
    } else {
        display_buffer_[2] = 0;
    }
}

void HT16K33Display::Clear() {
    for (size_t i = 0; i < 4; i++) {
        display_buffer_[i] = 0;
    }
}

void HT16K33Display::WriteDisplay() {
    write_start();
    write_raw(0x0);
    write_raw(display_buffer_, 4);
    write_stop();
}

void HT16K33Display::enable_oscillator() {
    write_start();
    write_raw(0x21);
    write_stop();
}

void HT16K33Display::write_start() {
    I2C_WAIT_FOR_FLAG(I2Cx, I2C_FLAG_BUSY);
    I2C_GenerateSTART(I2Cx, ENABLE);
    I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_MODE_SELECT);
    I2C_Send7bitAddress(I2Cx, device_address_, I2C_Direction_Transmitter);
    I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
}

void HT16K33Display::write_stop() {
    I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
    I2C_GenerateSTOP(I2Cx, ENABLE);
}

void HT16K33Display::write_raw(uint16_t* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        I2C_SendData(I2Cx, data[i] & 0xFF);
        I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
        I2C_SendData(I2Cx, data[i] >> 8);
        I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
    }
}

void HT16K33Display::write_raw(uint8_t data) {
    write_raw(&data, 1);
}

void HT16K33Display::write_raw(uint8_t* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        I2C_SendData(I2Cx, data[i]);
        I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
    }
}
