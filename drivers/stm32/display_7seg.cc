#include "drivers/stm32/display_7seg.h"

static constexpr uint8_t MAX_DIGITS = 8;

static const uint8_t SYMBOL_TABLE[] = {
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
    0x02, // :
    0x00, // am/pm
    0x7C, // b
    0x5E, // d
    0x73, // P
    0x1C, // v
    0x3F, // O
    0x38, // L
};

#define SWAP_ENDIANNESS(v) { \
        if (segment_endianness_ == SegmentEndianness::BIG) { \
            v = __RBIT((v)) >> 25;                           \
        } \
    }

static uint16_t u16pow(uint8_t base, uint8_t exp) {
    uint16_t p = base;
    for (uint8_t i = 0; i < exp-1; i++) {
        p *= base;
    }
    return p;
}

Display7Seg::Display7Seg(I2CBus& i2c_bus,
                         uint8_t device_address,
                         uint8_t n_digits,
                         uint8_t first_digit_register,
                         const WriteMode write_mode,
                         const SegmentEndianness segment_endianness)
    : i2c_bus_(i2c_bus),
      device_address_(device_address),
      n_digits_(n_digits > MAX_DIGITS ? MAX_DIGITS : n_digits),
      first_digit_register_(first_digit_register),
      write_mode_(write_mode),
      segment_endianness_(segment_endianness)
{}

// Set a single number 1 - 9, in the display. Value number positions are 0, 1, 3, 4. Position 2 is the colon.
void Display7Seg::SetNumber(uint8_t pos, uint8_t number, bool dot) {
    if (pos > n_digits_ || pos == 2) {
        pos = 0;
    }
    if (number > 9) {
        number = 0;
    }
    uint32_t value = SYMBOL_TABLE[number];
    SWAP_ENDIANNESS(value);
    value |= (dot << 7);
    display_buffer_[pos] = value;
}

// Set a whole number, no greater than MAX_DISPLAY_NUMBER. If the
// number specified is greater than MAX_DISPLAY_NUMBER, set it to
// MAX_DISPLAY_NUMBER.
void Display7Seg::SetNumber(uint16_t number) {
    const uint16_t max_display_number = u16pow(10, n_digits_) - 1;
    if (number > max_display_number) {
        number = max_display_number;
    }
    uint16_t scale = u16pow(10, n_digits_-2);
    uint8_t last_value = 0;
    uint16_t remaining = number;

    // Special case 0, because of display padding
    if (number == 0) {
        SetNumber(n_digits_-1, 0, false);
        return;
    }

    bool non_zero_written = false;
    for (size_t i = 0; i < n_digits_; i++) {
        if (i == 2) {
            // Skip colon position
            continue;
        }
        last_value = remaining / scale;
        if (last_value != 0 || non_zero_written) {
            SetNumber(i, last_value, false);
            non_zero_written = true;
        }

        remaining = remaining - (last_value * scale);
        scale /= 10;
    }
}

void Display7Seg::SetChar(uint8_t pos, char ch) {
    if (pos > n_digits_ || pos == 2) {
        pos = 0;
    }
    switch (ch) {
        case 'b':
            display_buffer_[pos] = SYMBOL_TABLE[12];
            break;
        case 'd':
            display_buffer_[pos] = SYMBOL_TABLE[13];
            break;
        case 'P':
            display_buffer_[pos] = SYMBOL_TABLE[14];
            break;
        case 'v':
            display_buffer_[pos] = SYMBOL_TABLE[15];
            break;
        case 'O':
            display_buffer_[pos] = SYMBOL_TABLE[16];
            break;
        case 'L':
            display_buffer_[pos] = SYMBOL_TABLE[17];
            break;
        default:
            break;
    }

    SWAP_ENDIANNESS(display_buffer_[pos]);
}


// Set a specific segment within a position. Segments are 0 - 7. Segment 7 is the dot to the right of the digit.
// Segment 0 is the middle LED, other segments move clockwise around the digit, starting at the top-most led (Top led = 1)
// LED (Think: The middle bar on an 8). See a picture here: https://www.adafruit.com/product/880 ... Segment 0 = A.
void Display7Seg::SetSegment(uint8_t pos, uint8_t segment, bool on, bool dot) {
    if (pos > n_digits_ || pos == 2) {
        pos = 0;
    }
    if (segment > 6) {
        segment = 0;
    }
    uint32_t value = (on << segment);
    SWAP_ENDIANNESS(value);
    value |= (dot << 7);
    display_buffer_[pos] |= (uint8_t)value;
}

void Display7Seg::ToggleColon(bool on) {
    if (on) {
        display_buffer_[2] = SYMBOL_TABLE[10];
    } else {
        display_buffer_[2] = 0;
    }
}

void Display7Seg::Clear() {
    for (size_t i = 0; i < n_digits_; i++) {
        display_buffer_[i] = 0;
    }
}

void Display7Seg::WriteDisplay() {
    if (write_mode_ == WriteMode::ONE_SHOT) {
        i2c_bus_.WriteTransmitStart(device_address_);
        i2c_bus_.WriteRaw(first_digit_register_);
        i2c_bus_.WriteRaw(display_buffer_, n_digits_);
        i2c_bus_.WriteTransmitStop();
    } else if (write_mode_ == WriteMode::SEPARATE) {
        for (int i = 0; i < n_digits_; i++) {
            i2c_bus_.WriteTransmitStart(device_address_);
            i2c_bus_.WriteRaw(first_digit_register_ + i);
            i2c_bus_.WriteRaw(display_buffer_[i]);
            i2c_bus_.WriteTransmitStop();
        }
    }
}

