#ifndef DISPLAY_7SEG_H
#define DISPLAY_7SEG_H

#include <cstddef>

#include "i2c_bus.h"

class Display7Seg {
public:
    enum WriteMode {
        ONE_SHOT,
        SEPARATE
    };

    Display7Seg(I2CBus& i2c_bus,
                uint8_t n_digits,
                uint8_t device_address,
                uint8_t first_digit_register,
                const WriteMode write_mode,
                const uint8_t* symbol_table);

    ~Display7Seg() = default;
    
    virtual void Init() = 0;
    virtual void SetBrightness(uint8_t brightness) = 0;

    void Clear();
    void ToggleColon(bool on);
    void SetNumber(uint8_t pos, uint8_t number, bool dot);
    void SetNumber(uint16_t number);
    void SetChar(uint8_t pos, char ch);
    void SetSegment(uint8_t pos, uint8_t segment, bool on, bool dot);
    void WriteDisplay();

protected:
    I2CBus& i2c_bus_;
    const uint8_t device_address_;
    const uint8_t n_digits_;
    const uint8_t first_digit_register_;
    const WriteMode write_mode_;
    const uint8_t* symbol_table_;
    
    uint16_t display_buffer_[4];
};

#endif
