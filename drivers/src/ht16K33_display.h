#ifndef HT16K33_DISPLAY_H
#define HT16K33_DISPLAY_H

#include <cstddef>

#include "i2c_bus.h"

class HT16K33Display {
public:
    HT16K33Display(I2CBus& i2c_bus,
                   uint8_t device_address);
    HT16K33Display(I2CBus& i2c_bus);

    ~HT16K33Display() = default;
    
    void Init();
    void Clear();
    void ToggleColon(bool on);
    void SetBrightness(uint8_t brightness);
    void SetBlinkRate(uint8_t blink_rate);
    void SetNumber(uint8_t pos, uint8_t number, bool dot);
    void SetNumber(uint16_t number);
    void SetChar(uint8_t pos, char ch);
    void SetSegment(uint8_t pos, uint8_t segment, bool on, bool dot);
    void WriteDisplay();

private:
    I2CBus& i2c_bus_;
    uint8_t device_address_;
    uint16_t display_buffer_[4];

    void enable_oscillator();
};

#endif
