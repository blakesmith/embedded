#include <stm32f4xx.h>
#include <cassert>

#include "drivers/stm32/pec11_renc.h"

/**
 * Computed from the quadrature output table. Algorithm is:
 * 1. Start with pin state 0b00 (both pins low)
 * 2. Moving through the table clockwise, shift the previous two bits twice. Append next bit state to the lower 2 bits of the 4-bit integer. These get assigned ENC_ACTION_ROTATE_CLOCKWISE
 * 3. Moving through the table counter clockwise, shift the previous two bits twice. Append next bit state to the lower 2 bits of the 4-bit integer. These get assigned ENC_ACTION_ROTATE_COUNTER_CLOCKWISE
 * 4. Go through each state in the table again, and repeat each state for the upper and lower bits of the 4-bit integer. These get assigned ENC_ACTION_NONE.
 * 5. Each bit state is equal to an integer between 0 - 15 (The array length of the table below), the value is the direction of the direction the state should move.
 * 6. Any gaps in the table get assigned a value of ENC_ACTION_NONE.
 */
static const RotationAction encoder_actions_by_state[] = {
    ENC_ACTION_NONE,
    ENC_ACTION_ROTATE_COUNTER_CLOCKWISE,
    ENC_ACTION_ROTATE_CLOCKWISE,
    ENC_ACTION_NONE,
    ENC_ACTION_ROTATE_CLOCKWISE,
    ENC_ACTION_NONE,
    ENC_ACTION_NONE,
    ENC_ACTION_ROTATE_COUNTER_CLOCKWISE,
    ENC_ACTION_ROTATE_COUNTER_CLOCKWISE,
    ENC_ACTION_NONE,
    ENC_ACTION_NONE,
    ENC_ACTION_ROTATE_CLOCKWISE,
    ENC_ACTION_NONE,
    ENC_ACTION_ROTATE_CLOCKWISE,
    ENC_ACTION_ROTATE_COUNTER_CLOCKWISE,
    ENC_ACTION_NONE,
};

static const ButtonAction button_actions_by_state[] = {
    BUTTON_ACTION_NONE,
    BUTTON_ACTION_DOWN,
    BUTTON_ACTION_NONE,
    BUTTON_ACTION_UP
};

static inline uint8_t read_pin(uint32_t pin_state, uint8_t pin) {
    return (pin_state & pin) != (uint32_t)Bit_RESET ? (uint8_t)Bit_SET : (uint8_t)Bit_RESET;
}

Pec11RotaryEncoder::Pec11RotaryEncoder(GPIOPin& clockwise_pin,
                                       GPIOPin& counter_clockwise_pin,
                                       GPIOPin& button_pin)
    : clockwise_pin_(clockwise_pin),
      counter_clockwise_pin_(counter_clockwise_pin),
      button_pin_(button_pin),
      rotation_state_(0),
      button_state_(0),
      encoder_count_(0),
      button_action_(BUTTON_ACTION_NONE) {
    assert(clockwise_pin_.get_bus() == counter_clockwise_pin_.get_bus());
    assert(counter_clockwise_pin_.get_bus() == button_pin_.get_bus());
}

void Pec11RotaryEncoder::Init() {
    clockwise_pin_.set_mode(GPIOPin::Mode::IN);
    clockwise_pin_.set_pupd(GPIOPin::PuPd::UP);
    clockwise_pin_.set_output(GPIOPin::OType::PUSH_PULL);
    clockwise_pin_.set_speed(GPIOPin::Speed::TWO_MHZ);

    counter_clockwise_pin_.set_mode(GPIOPin::Mode::IN);
    counter_clockwise_pin_.set_pupd(GPIOPin::PuPd::UP);
    counter_clockwise_pin_.set_output(GPIOPin::OType::PUSH_PULL);
    counter_clockwise_pin_.set_speed(GPIOPin::Speed::TWO_MHZ);

    button_pin_.set_mode(GPIOPin::Mode::IN);
    button_pin_.set_pupd(GPIOPin::PuPd::UP);
    button_pin_.set_output(GPIOPin::OType::PUSH_PULL);
    button_pin_.set_speed(GPIOPin::Speed::TWO_MHZ);

    clockwise_pin_.Init();
    counter_clockwise_pin_.Init();
    button_pin_.Init();
}

RotationAction Pec11RotaryEncoder::rotation_action(uint32_t pin_state) {
    uint8_t cw_pin = read_pin(pin_state, clockwise_pin_.get_pin_number());
    uint8_t ccw_pin = read_pin(pin_state, counter_clockwise_pin_.get_pin_number());
    rotation_state_ <<= 2; // Retain the previous pin state as the upper two bits
    rotation_state_ |= ((cw_pin << 1) | ccw_pin) & 0x03; // Shift the current state onto the lower 2 bits
    return encoder_actions_by_state[rotation_state_ & 0x0F]; // Only keep the bottom 4 bits, throw away the upper 4, lookup in table
}

ButtonAction Pec11RotaryEncoder::button_action(uint32_t pin_state) {
    uint8_t button_pin = read_pin(pin_state, button_pin_.get_pin_number());
    button_state_ <<= 1;
    button_state_ |= ~button_pin & 0x01;
    return button_actions_by_state[button_state_ & 0x03];
}

void Pec11RotaryEncoder::ResetCount() {
    encoder_count_ = 0;
}

void Pec11RotaryEncoder::ReadState() {
    uint32_t pin_state = clockwise_pin_.get_bus().ReadAll();
    encoder_count_ += (int8_t)rotation_action(pin_state);
    button_action_ = button_action(pin_state);
}

long Pec11RotaryEncoder::GetCount() {
    return encoder_count_ / 4;
}

ButtonAction Pec11RotaryEncoder::GetButtonAction() {
    return button_action_;
}

