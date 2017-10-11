#include <stm32f4xx.h>

#include "pec11_renc.h"

#define CLOCKWISE_PIN GPIO_Pin_2
#define CLOCKWISE_PINSOURCE EXTI_PinSource2
#define CLOCKWISE_GPIO GPIOE
#define CLOCKWISE_EXTI_LINE EXTI_Line2
#define CLOCKWISE_EXTI_PORTSOURCE EXTI_PortSourceGPIOE
#define CLOCKWISE_NVIC_IRQ_CHANNEL EXTI2_IRQn

#define COUNTER_CLOCKWISE_PIN GPIO_Pin_6
#define COUNTER_CLOCKWISE_PINSOURCE EXTI_PinSource6
#define COUNTER_CLOCKWISE_GPIO GPIOD
#define COUNTER_CLOCKWISE_EXTI_LINE EXTI_Line6
#define COUNTER_CLOCKWISE_EXTI_PORTSOURCE EXTI_PortSourceGPIOD
#define COUNTER_CLOCKWISE_NVIC_IRQ_CHANNEL EXTI9_5_IRQn

#define BUTTON_PIN GPIO_Pin_1
#define BUTTON_PINSOURCE EXTI_PinSource1
#define BUTTON_GPIO GPIOC
#define BUTTON_EXTI_LINE EXTI_Line1
#define BUTTON_EXTI_PORTSOURCE EXTI_PortSourceGPIOC
#define BUTTON_NVIC_IRQ_CHANNEL EXTI1_IRQn


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

Pec11RotaryEncoder::Pec11RotaryEncoder()
    : encoder_state_(0),
      encoder_count_(0),
      button_pressed_(false) { }

void Pec11RotaryEncoder::Init() {
    GPIO_InitTypeDef encoder_gpio;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_StructInit(&encoder_gpio);
    encoder_gpio.GPIO_Pin = CLOCKWISE_PIN;
    encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(CLOCKWISE_GPIO, &encoder_gpio);

    GPIO_StructInit(&encoder_gpio);
    encoder_gpio.GPIO_Pin = COUNTER_CLOCKWISE_PIN;
    encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(COUNTER_CLOCKWISE_GPIO, &encoder_gpio);

    GPIO_StructInit(&encoder_gpio);
    encoder_gpio.GPIO_Pin = BUTTON_PIN;
    encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_UP;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(BUTTON_GPIO, &encoder_gpio);
}

EncoderAction Pec11RotaryEncoder::lookup_action() {
    bool cw_high = GPIO_ReadInputDataBit(CLOCKWISE_GPIO, CLOCKWISE_PIN);
    bool ccw_high = GPIO_ReadInputDataBit(COUNTER_CLOCKWISE_GPIO, COUNTER_CLOCKWISE_PIN);
    encoder_state_ <<= 2; // Retain the previous pin state as the upper two bits
    encoder_state_ &= 0x0F; // Only keep the bottom 4 bits, throw away the upper 4
    encoder_state_ |= ((cw_high << 1) | ccw_high); // Shift the current state onto the lower 2 bits
    return encoder_actions_by_state[encoder_state_];
}

void Pec11RotaryEncoder::ResetCount() {
    encoder_count_ = 0;
}

void Pec11RotaryEncoder::ReadState() {
    encoder_count_ += lookup_action();
    button_pressed_ = !static_cast<bool>(GPIO_ReadInputDataBit(BUTTON_GPIO, BUTTON_PIN));
}

long Pec11RotaryEncoder::GetCount() {
    return encoder_count_;
}

bool Pec11RotaryEncoder::GetAndClearButtonPressed() {
    bool pressed = button_pressed_;
    if (pressed) {
        button_pressed_ = false;
    }
    return pressed;
}

