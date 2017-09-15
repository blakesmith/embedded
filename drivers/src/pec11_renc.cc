#include <stm32f4xx.h>

#include "pec11_renc.h"

#define CLOCKWISE_PIN GPIO_Pin_2
#define CLOCKWISE_PINSOURCE EXTI_PinSource2
#define CLOCKWISE_IDR GPIO_IDR_IDR_2
#define CLOCKWISE_GPIO GPIOE
#define CLOCKWISE_EXTI_LINE EXTI_Line2
#define CLOCKWISE_EXTI_PORTSOURCE EXTI_PortSourceGPIOE
#define CLOCKWISE_NVIC_IRQ_CHANNEL EXTI2_IRQn

#define COUNTER_CLOCKWISE_PIN GPIO_Pin_6
#define COUNTER_CLOCKWISE_PINSOURCE EXTI_PinSource6
#define COUNTER_CLOCKWISE_IDR GPIO_IDR_IDR_6
#define COUNTER_CLOCKWISE_GPIO GPIOD
#define COUNTER_CLOCKWISE_EXTI_LINE EXTI_Line6
#define COUNTER_CLOCKWISE_EXTI_PORTSOURCE EXTI_PortSourceGPIOD
#define COUNTER_CLOCKWISE_NVIC_IRQ_CHANNEL EXTI9_5_IRQn

void Pec11RotaryEncoder::setup_clockwise() {
    EXTI_InitTypeDef encoder_exti;
    NVIC_InitTypeDef encoder_nvic;

    SYSCFG_EXTILineConfig(CLOCKWISE_EXTI_PORTSOURCE, CLOCKWISE_PINSOURCE);

    encoder_exti.EXTI_Line = CLOCKWISE_EXTI_LINE;
    encoder_exti.EXTI_LineCmd = ENABLE;
    encoder_exti.EXTI_Mode = EXTI_Mode_Interrupt;
    encoder_exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&encoder_exti);

    encoder_nvic.NVIC_IRQChannel = CLOCKWISE_NVIC_IRQ_CHANNEL;
    encoder_nvic.NVIC_IRQChannelPreemptionPriority = 0;
    encoder_nvic.NVIC_IRQChannelSubPriority = 0x0;
    encoder_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&encoder_nvic);
}

void Pec11RotaryEncoder::setup_counter_clockwise() {
    EXTI_InitTypeDef encoder_exti;
    NVIC_InitTypeDef encoder_nvic;
    
    SYSCFG_EXTILineConfig(COUNTER_CLOCKWISE_EXTI_PORTSOURCE, COUNTER_CLOCKWISE_PINSOURCE);

    encoder_exti.EXTI_Line = COUNTER_CLOCKWISE_EXTI_LINE;
    encoder_exti.EXTI_LineCmd = ENABLE;
    encoder_exti.EXTI_Mode = EXTI_Mode_Interrupt;
    encoder_exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&encoder_exti);

    encoder_nvic.NVIC_IRQChannel = COUNTER_CLOCKWISE_NVIC_IRQ_CHANNEL;
    encoder_nvic.NVIC_IRQChannelPreemptionPriority = 0;
    encoder_nvic.NVIC_IRQChannelSubPriority = 0x01;
    encoder_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&encoder_nvic);
}

void Pec11RotaryEncoder::Init() {
    GPIO_InitTypeDef encoder_gpio;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_StructInit(&encoder_gpio);
    encoder_gpio.GPIO_Pin = CLOCKWISE_PIN;
    encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_UP;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(CLOCKWISE_GPIO, &encoder_gpio);

    GPIO_StructInit(&encoder_gpio);
    encoder_gpio.GPIO_Pin = COUNTER_CLOCKWISE_PIN;
    encoder_gpio.GPIO_Mode = GPIO_Mode_IN;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_UP;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(COUNTER_CLOCKWISE_GPIO, &encoder_gpio);

    setup_clockwise();
    setup_counter_clockwise();
}

void Pec11RotaryEncoder::disable_irq() {
    NVIC_InitTypeDef encoder_nvic;
    
    encoder_nvic.NVIC_IRQChannel = CLOCKWISE_NVIC_IRQ_CHANNEL;
    encoder_nvic.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&encoder_nvic);

    encoder_nvic.NVIC_IRQChannel = COUNTER_CLOCKWISE_NVIC_IRQ_CHANNEL;
    encoder_nvic.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&encoder_nvic);
}

void Pec11RotaryEncoder::enable_irq() {
    NVIC_InitTypeDef encoder_nvic;
    
    encoder_nvic.NVIC_IRQChannel = CLOCKWISE_NVIC_IRQ_CHANNEL;
    encoder_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&encoder_nvic);

    encoder_nvic.NVIC_IRQChannel = COUNTER_CLOCKWISE_NVIC_IRQ_CHANNEL;
    encoder_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&encoder_nvic);
}


EncoderAction Pec11RotaryEncoder::GetAction() {
    EncoderAction action = ENC_ACTION_NONE;

    disable_irq();
    
    if (EXTI_GetITStatus(CLOCKWISE_EXTI_LINE) != RESET) {
        action = ENC_ACTION_ROTATE_CLOCKWISE;
        EXTI_ClearITPendingBit(CLOCKWISE_EXTI_LINE);
    }
    if (EXTI_GetITStatus(COUNTER_CLOCKWISE_EXTI_LINE) != RESET) {
        action = ENC_ACTION_ROTATE_COUNTER_CLOCKWISE;
        EXTI_ClearITPendingBit(COUNTER_CLOCKWISE_EXTI_LINE);
    }

    enable_irq();
    return action;
}

