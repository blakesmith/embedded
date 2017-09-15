#include <stm32f4xx.h>

#include "pec11_renc.h"

#define CLOCKWISE_PIN GPIO_Pin_2
#define CLOCKWISE_PINSOURCE EXTI_PinSource2
#define CLOCKWISE_IDR GPIO_IDR_IDR_2
#define CLOCKWISE_GPIO GPIOE
#define EXTI_CLOCKWISE_PORTSOURCE EXTI_PortSourceGPIOE
#define CLOCKWISE_EXTI_LINE EXTI_Line2
#define CLOCKWISE_NVIC_IRQ_CHANNEL EXTI2_IRQn

#define COUNTER_CLOCKWISE_PIN GPIO_Pin_5
#define COUNTER_CLOCKWISE_PINSOURCE EXTI_PinSource5
#define COUNTER_CLOCKWISE_IDR GPIO_IDR_IDR_5
#define COUNTER_CLOCKWISE_GPIO GPIOE
#define COUNTER_CLOCKWISE_EXTI_LINE EXTI_Line5
#define EXTI_COUNTER_CLOCKWISE_PORTSOURCE EXTI_PortSourceGPIOE
#define COUNTER_CLOCKWISE_NVIC_IRQ_CHANNEL EXTI9_5_IRQn

#define BUTTON_PIN GPIO_Pin_3
#define BUTTON_PINSOURCE EXTI_PinSource3
#define BUTTON_IDR GPIO_IDR_IDR_3


Pec11RotaryEncoder::Pec11RotaryEncoder() :
    cw_pin_state_(read_pin_state(CLOCKWISE_IDR)),
    ccw_pin_state_(read_pin_state(COUNTER_CLOCKWISE_IDR)),
    button_pin_state_(read_pin_state(BUTTON_IDR)) { }

void Pec11RotaryEncoder::Init() {
    GPIO_InitTypeDef encoder_gpio;
    EXTI_InitTypeDef encoder_exti;
    NVIC_InitTypeDef encoder_nvic;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_StructInit(&encoder_gpio);
    encoder_gpio.GPIO_Pin = CLOCKWISE_PIN;
    encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_UP;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CLOCKWISE_GPIO, &encoder_gpio);

    // GPIO_StructInit(&encoder_gpio);
    // encoder_gpio.GPIO_Pin = COUNTER_CLOCKWISE_PIN;
    // encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    // encoder_gpio.GPIO_PuPd = GPIO_PuPd_UP;
    // encoder_gpio.GPIO_OType = GPIO_OType_PP;
    // encoder_gpio.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(COUNTER_CLOCKWISE_GPIO, &encoder_gpio);

    SYSCFG_EXTILineConfig(EXTI_CLOCKWISE_PORTSOURCE, CLOCKWISE_PINSOURCE);
//    SYSCFG_EXTILineConfig(EXTI_COUNTER_CLOCKWISE_PORTSOURCE, COUNTER_CLOCKWISE_PINSOURCE);
//    SYSCFG_EXTILineConfig(EXTI_PORTSOURCE, BUTTON_PINSOURCE);

    encoder_exti.EXTI_Line = CLOCKWISE_EXTI_LINE;
    encoder_exti.EXTI_LineCmd = ENABLE;
    encoder_exti.EXTI_Mode = EXTI_Mode_Interrupt;
    encoder_exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&encoder_exti);

    encoder_nvic.NVIC_IRQChannel = CLOCKWISE_NVIC_IRQ_CHANNEL;
    encoder_nvic.NVIC_IRQChannelPreemptionPriority = 0;
    encoder_nvic.NVIC_IRQChannelSubPriority = 0;
    encoder_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&encoder_nvic);
}

EncoderAction Pec11RotaryEncoder::GetAction() {
    PinState ps;
    EncoderAction action;
    
    if (EXTI_GetITStatus(CLOCKWISE_EXTI_LINE) != RESET) {
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
        
        EXTI_ClearITPendingBit(CLOCKWISE_EXTI_LINE);
        return action;
    }

    return ENC_ACTION_NONE;
}

PinState Pec11RotaryEncoder::read_pin_state(uint32_t idr) {
    if (CLOCKWISE_GPIO->IDR & idr) {
        return PIN_STATE_HIGH;
    } else {
        return PIN_STATE_LOW;
    }
}
