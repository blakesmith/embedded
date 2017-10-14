#include <stm32f4xx.h>

#include "pec11_renc.h"

static constexpr uint32_t GPIO_CLOCK = RCC_AHB1Periph_GPIOD;
static GPIO_TypeDef *GPIOx = GPIOD;
static constexpr uint8_t CLOCKWISE_PIN = GPIO_Pin_2;
static constexpr uint8_t COUNTER_CLOCKWISE_PIN = GPIO_Pin_3;
static constexpr uint8_t BUTTON_PIN = GPIO_Pin_6;


/**
 * Computed from the quadrature output table. Algorithm is:
 * 1. Start with pin state 0b00 (both pins low)
 * 2. Moving through the table clockwise, shift the previous two bits twice. Append next bit state to the lower 2 bits of the 4-bit integer. These get assigned ENC_ACTION_ROTATE_CLOCKWISE
 * 3. Moving through the table counter clockwise, shift the previous two bits twice. Append next bit state to the lower 2 bits of the 4-bit integer. These get assigned ENC_ACTION_ROTATE_COUNTER_CLOCKWISE
 * 4. Go through each state in the table again, and repeat each state for the upper and lower bits of the 4-bit integer. These get assigned ENC_ACTION_NONE.
 * 5. Each bit state is equal to an integer between 0 - 15 (The array length of the table below), the value is the direction of the direction the state should move.
 * 6. Any gaps in the table get assigned a value of ENC_ACTION_NONE.
 */
static const EncoderAction encoder_actions_by_state[] = {
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

static inline uint8_t read_pin(uint32_t pin_state, uint8_t pin) {
    return (pin_state & pin) != (uint32_t)Bit_RESET ? (uint8_t)Bit_SET : (uint8_t)Bit_RESET;
}

Pec11RotaryEncoder::Pec11RotaryEncoder()
    : encoder_state_(0),
      encoder_count_(0),
      button_pressed_(false) { }

void Pec11RotaryEncoder::Init() {
    GPIO_InitTypeDef encoder_gpio;

    RCC_AHB1PeriphClockCmd(GPIO_CLOCK, ENABLE);

    GPIO_StructInit(&encoder_gpio);
    encoder_gpio.GPIO_Pin = CLOCKWISE_PIN | COUNTER_CLOCKWISE_PIN | BUTTON_PIN;
    encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_UP;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOx, &encoder_gpio);
}

EncoderAction Pec11RotaryEncoder::lookup_action(uint32_t pin_state) {
    uint8_t cw_high = read_pin(pin_state, CLOCKWISE_PIN);
    uint8_t ccw_high = read_pin(pin_state, COUNTER_CLOCKWISE_PIN);
    encoder_state_ <<= 2; // Retain the previous pin state as the upper two bits
    encoder_state_ |= ((cw_high << 1) | ccw_high) & 0x03; // Shift the current state onto the lower 2 bits
    return encoder_actions_by_state[encoder_state_ & 0x0F]; // Only keep the bottom 4 bits, throw away the upper 4, lookup in table
}

void Pec11RotaryEncoder::ResetCount() {
    encoder_count_ = 0;
}

void Pec11RotaryEncoder::ReadState() {
    uint32_t pin_state = GPIOx->IDR;
    encoder_count_ += (int8_t)lookup_action(pin_state);
    button_pressed_ = !static_cast<bool>(read_pin(pin_state, BUTTON_PIN));
}

long Pec11RotaryEncoder::GetCount() {
    return encoder_count_;
}

bool Pec11RotaryEncoder::GetButtonPressed() {
    return button_pressed_;
}

