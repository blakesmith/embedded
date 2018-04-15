#ifndef DISPLAY_7SEG_H
#define DISPLAY_7SEG_H

#include <cstddef>

#include "i2c_bus.h"

class Display7Seg {
public:
    enum WriteMode {
        ONE_SHOT, // Write all the display data in one i2c transmission
        SEPARATE  // Break up each display digit into its own i2c transmission
    };

    // Some displays flip the bits of each digit segment. Match the endianness, so we can
    // set the correct segments, and flip numbers from the symbol table.
    enum SegmentEndianness {
        BIG,
        LITTLE
    };

    Display7Seg(I2CBus& i2c_bus,
                uint8_t n_digits,
                uint8_t device_address,
                uint8_t first_digit_register,
                const WriteMode write_mode,
                const SegmentEndianness segment_endianess);

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
    const SegmentEndianness segment_endianness_;
    
    uint16_t display_buffer_[4];
};

#endif
