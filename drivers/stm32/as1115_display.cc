#include "drivers/stm32/as1115_display.h"

static constexpr uint8_t FIRST_DIGIT_REGISTER = 0x01;

static constexpr uint8_t DEFAULT_DEVICE_ADDRESS = 0x0;

static constexpr uint8_t AS1115_CMD_DECODE = 0x09;
static constexpr uint8_t AS1115_CMD_INTENSITY = 0x0A;
static constexpr uint8_t AS1115_CMD_SCAN_LIMIT = 0x0B;
static constexpr uint8_t AS1115_CMD_SHUTDOWN = 0x0C;
static constexpr uint8_t AS1115_CMD_FEATURE = 0x0E;

AS1115Display::AS1115Display(I2CBus& i2c_bus,
                             uint8_t n_digits,
                             uint8_t device_address)
    : Display7Seg(i2c_bus,
                  device_address,
                  n_digits,
                  FIRST_DIGIT_REGISTER,
                  Display7Seg::WriteMode::SEPARATE,
                  Display7Seg::SegmentEndianness::BIG)
{}

AS1115Display::AS1115Display(I2CBus& i2c_bus,
                             uint8_t n_digits)
    : Display7Seg(i2c_bus,
                  DEFAULT_DEVICE_ADDRESS,
                  n_digits,
                  FIRST_DIGIT_REGISTER,
                  Display7Seg::WriteMode::SEPARATE,
                  Display7Seg::SegmentEndianness::BIG)
{}

void AS1115Display::Init() {
    wakeup();

    // Set scan limit, 5 digits
    set_scan_limit(0x05);

    SetBrightness(15);

    disable_decode();

    Clear();
    WriteDisplay();
}

void AS1115Display::wakeup() {
    i2c_bus_.WriteTransmitStart(device_address_);
    i2c_bus_.WriteRaw(AS1115_CMD_SHUTDOWN);
    i2c_bus_.WriteRaw(0x01);
    i2c_bus_.WriteTransmitStop();
}

void AS1115Display::disable_decode() {
    i2c_bus_.WriteTransmitStart(device_address_);
    i2c_bus_.WriteRaw(AS1115_CMD_DECODE);
    i2c_bus_.WriteRaw(0x00);
    i2c_bus_.WriteTransmitStop();
}

void AS1115Display::SimpleWrite(uint8_t digit) {
    i2c_bus_.WriteTransmitStart(device_address_);
    i2c_bus_.WriteRaw(digit);
    i2c_bus_.WriteRaw(0xFF);
    i2c_bus_.WriteTransmitStop();
}

void AS1115Display::set_scan_limit(uint8_t limit) {
    if (limit > 7) {
        limit = 0;
    }
    i2c_bus_.WriteTransmitStart(device_address_);
    i2c_bus_.WriteRaw(AS1115_CMD_SCAN_LIMIT);
    i2c_bus_.WriteRaw(limit);
    i2c_bus_.WriteTransmitStop();
}

void AS1115Display::SetBrightness(uint8_t brightness) {
    if (brightness > 15) {
        brightness = 15;
    }
    i2c_bus_.WriteTransmitStart(device_address_);
    i2c_bus_.WriteRaw(AS1115_CMD_INTENSITY);
    i2c_bus_.WriteRaw(brightness);
    i2c_bus_.WriteTransmitStop();
}
