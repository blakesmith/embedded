#include "drivers/stm32/display_7seg.h"

static constexpr uint8_t MAX_DIGITS = 8;

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
                         const uint8_t* symbol_table)
    : i2c_bus_(i2c_bus),
      device_address_(device_address),
      n_digits_(n_digits > MAX_DIGITS ? MAX_DIGITS : n_digits),
      first_digit_register_(first_digit_register),
      symbol_table_(symbol_table)
{}

// Set a single number 1 - 9, in the display. Value number positions are 0, 1, 3, 4. Position 2 is the colon.
void Display7Seg::SetNumber(uint8_t pos, uint8_t number, bool dot) {
    if (pos > n_digits_ || pos == 2) {
        pos = 0;
    }
    if (number > 9) {
        number = 0;
    }
    uint8_t value = symbol_table_[number] | (dot << 7);
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
            display_buffer_[pos] = symbol_table_[12];
            break;
        case 'd':
            display_buffer_[pos] = symbol_table_[13];
            break;
        case 'P':
            display_buffer_[pos] = symbol_table_[14];
            break;
        case 'v':
            display_buffer_[pos] = symbol_table_[15];
            break;
        case 'O':
            display_buffer_[pos] = symbol_table_[16];
            break;
        case 'L':
            display_buffer_[pos] = symbol_table_[17];
            break;
        default:
            break;
    }
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
    uint8_t value = (on << segment) | (dot << 7);
    display_buffer_[pos] |= value;
}

void Display7Seg::ToggleColon(bool on) {
    if (on) {
        display_buffer_[2] = symbol_table_[10];
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
    for (int i = 0; i < n_digits_; i++) {
        i2c_bus_.WriteTransmitStart(device_address_);
        i2c_bus_.WriteRaw(first_digit_register_ + i);
        i2c_bus_.WriteRaw(display_buffer_[i]);
        i2c_bus_.WriteTransmitStop();
    }
}

