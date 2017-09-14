#include <stm32f4xx.h>

#include "pec11_renc.h"

#define CLOCKWISE_PIN GPIO_Pin_1
#define CLOCKWISE_PINSOURCE EXTI_PinSource1
#define CLOCKWISE_IDR GPIO_IDR_IDR_1

#define COUNTER_CLOCKWISE_PIN GPIO_Pin_2
#define COUNTER_CLOCKWISE_PINSOURCE EXTI_PinSource2
#define COUNTER_CLOCKWISE_IDR GPIO_IDR_IDR_2

#define BUTTON_PIN GPIO_Pin_3
#define BUTTON_PINSOURCE EXTI_PinSource3
#define BUTTON_IDR GPIO_IDR_IDR_3

#define GPIOx GPIOA
#define EXTI_PORTSOURCE EXTI_PortSourceGPIOA
#define EXTI_LINE EXTI_Line0

Pec11RotaryEncoder::Pec11RotaryEncoder() :
    cw_pin_state_(read_pin_state(CLOCKWISE_IDR)),
    ccw_pin_state_(read_pin_state(COUNTER_CLOCKWISE_IDR)),
    button_pin_state_(read_pin_state(BUTTON_IDR)) { }

void Pec11RotaryEncoder::Init() {
    GPIO_InitTypeDef encoder_gpio;
    EXTI_InitTypeDef encoder_exti;
    NVIC_InitTypeDef encoder_nvic;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    encoder_gpio.GPIO_Pin = CLOCKWISE_PIN | COUNTER_CLOCKWISE_PIN | BUTTON_PIN;
    encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_UP;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOx, &encoder_gpio);

    SYSCFG_EXTILineConfig(EXTI_PORTSOURCE, CLOCKWISE_PINSOURCE);
    SYSCFG_EXTILineConfig(EXTI_PORTSOURCE, COUNTER_CLOCKWISE_PINSOURCE);
    SYSCFG_EXTILineConfig(EXTI_PORTSOURCE, BUTTON_PINSOURCE);

    encoder_exti.EXTI_Line = EXTI_LINE;
    encoder_exti.EXTI_LineCmd = ENABLE;
    encoder_exti.EXTI_Mode = EXTI_Mode_Interrupt;
    encoder_exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&encoder_exti);

    encoder_nvic.NVIC_IRQChannel = EXTI0_IRQn;
    encoder_nvic.NVIC_IRQChannelPreemptionPriority = 0;
    encoder_nvic.NVIC_IRQChannelSubPriority = 0;
    encoder_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&encoder_nvic);
}

EncoderAction Pec11RotaryEncoder::GetAction() {
    PinState ps;
    EncoderAction action;
    
    if (EXTI_GetITStatus(EXTI_LINE) != RESET) {
        ps = read_pin_state(CLOCKWISE_IDR);
        if (ps != cw_pin_state_) {
            cw_pin_state_ = ps;
            action = ENC_ACTION_ROTATE_CLOCKWISE;
        }
        ps = read_pin_state(COUNTER_CLOCKWISE_IDR);
        if (ps != ccw_pin_state_) {
            ccw_pin_state_ = ps;
            action = ENC_ACTION_ROTATE_COUNTER_CLOCKWISE;
        }
        ps = read_pin_state(BUTTON_IDR);
        if (ps != button_pin_state_) {
            button_pin_state_ = ps;
            action = ENC_ACTION_PUSH_BUTTON;
        }
        
        EXTI_ClearITPendingBit(EXTI_LINE);
        return action;
    }

    return ENC_ACTION_NONE;
}

PinState Pec11RotaryEncoder::read_pin_state(uint32_t idr) {
    if (GPIOx->IDR & idr) {
        return PIN_STATE_HIGH;
    } else {
        return PIN_STATE_LOW;
    }
}
