#include "drivers/stm32/ht16K33_display.h"

static constexpr uint8_t FIRST_DIGIT_REGISTER = 0x0;

// Default address.
static constexpr uint8_t DEFAULT_DEVICE_ADDRESS = 0x70 << 1;

static constexpr uint8_t HT16K33_BLINK_CMD = 0x80;
static constexpr uint8_t HT16K33_BLINK_OFF = 0;
static constexpr uint8_t HT16K33_BLINK_ON = 1;

static constexpr uint8_t HT16K33_CMD_BRIGHTNESS = 0xE0;

HT16K33Display::HT16K33Display(I2CBus& i2c_bus,
                               uint8_t device_address)
    : Display7Seg(i2c_bus, device_address, FIRST_DIGIT_REGISTER)
{}

HT16K33Display::HT16K33Display(I2CBus& i2c_bus)
    : Display7Seg(i2c_bus, DEFAULT_DEVICE_ADDRESS, FIRST_DIGIT_REGISTER)
{}


void HT16K33Display::Init() {
    enable_oscillator();
    set_blink_rate(HT16K33_BLINK_OFF);
    SetBrightness(15);

    Clear();
    WriteDisplay();
}

void HT16K33Display::SetBrightness(uint8_t brightness) {
    if (brightness > 15) {
        brightness = 15;
    }
    i2c_bus_.WriteTransmitStart(device_address_);
    i2c_bus_.WriteRaw(HT16K33_CMD_BRIGHTNESS | brightness);
    i2c_bus_.WriteTransmitStop();
}

void HT16K33Display::set_blink_rate(uint8_t rate) {
    if (rate > 3) {
        rate = 0;
    }
    i2c_bus_.WriteTransmitStart(device_address_);
    i2c_bus_.WriteRaw(HT16K33_BLINK_CMD | HT16K33_BLINK_ON | (rate << 1));
    i2c_bus_.WriteTransmitStop();
}

void HT16K33Display::enable_oscillator() {
    i2c_bus_.WriteTransmitStart(device_address_);
    i2c_bus_.WriteRaw(0x21);
    i2c_bus_.WriteTransmitStop();
}

