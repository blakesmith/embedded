#include "as1115_display.h"

static constexpr uint8_t FIRST_DIGIT_REGISTER = 0x01;

static constexpr uint8_t DEFAULT_DEVICE_ADDRESS = 0x0;

AS1115Display::AS1115Display(I2CBus& i2c_bus,
                            uint8_t device_address)
    : Display7Seg(i2c_bus, device_address, FIRST_DIGIT_REGISTER)
{}

AS1115Display::AS1115Display(I2CBus& i2c_bus)
    : Display7Seg(i2c_bus, DEFAULT_DEVICE_ADDRESS, FIRST_DIGIT_REGISTER)
{}

void AS1115Display::Init() {
}

void AS1115Display::SetBrightness(uint8_t brightness) {
}

void AS1115Display::SetBlinkRate(uint8_t rate) {
}
