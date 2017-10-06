#include <stm32f4xx.h>
#include <cstddef>

#include "ht16K33_display.h"
#include "pec11_renc.h"
#include "cs43l22_dac.h"

GPIO_InitTypeDef GPIO_LED;
HT16K33Display display;
Pec11RotaryEncoder knob;

void SetLedState(long count);

volatile uint32_t count = 0;

static const uint32_t states[] = {
    0,
    GPIO_Pin_12,
    GPIO_Pin_12 | GPIO_Pin_13,
    GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14,
    GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
    GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
    GPIO_Pin_14 | GPIO_Pin_15,
    GPIO_Pin_15,
};

static const size_t n_states = sizeof(states) / sizeof(uint32_t);

void InitOnboardLed() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    GPIO_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_LED.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_LED.GPIO_OType = GPIO_OType_PP;
    GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_LED);
}

void InitOnboardButton() {
    GPIO_InitTypeDef button_gpio;
    EXTI_InitTypeDef button_exti;
    NVIC_InitTypeDef button_nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    
    GPIO_StructInit(&button_gpio);
    button_gpio.GPIO_Pin = GPIO_Pin_0;
    button_gpio.GPIO_Mode = GPIO_Mode_IN;
    button_gpio.GPIO_OType = GPIO_OType_PP;
    button_gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
    button_gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &button_gpio);

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

    button_exti.EXTI_Line = EXTI_Line0;
    button_exti.EXTI_LineCmd = ENABLE;
    button_exti.EXTI_Mode = EXTI_Mode_Interrupt;
    button_exti.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&button_exti);

    button_nvic.NVIC_IRQChannel = EXTI0_IRQn;
    button_nvic.NVIC_IRQChannelPreemptionPriority = 0;
    button_nvic.NVIC_IRQChannelSubPriority = 0;
    button_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&button_nvic);
}

void Init() {
    InitOnboardLed();
//    InitOnboardButton();
    display.Init();
//    knob.Init();

    uint32_t rc = SysTick_Config(SystemCoreClock / 10);
    if (rc != 0) {
        GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
    }

    SetLedState(3);
}

void SetLedState(long count) {
    uint32_t pins = states[count % n_states];
    GPIOD->ODR = pins;
}

void UpdateDisplay() {
    display.Clear();
    for (size_t i = 0; i < 5; i++) {
        uint8_t segment = count % 7;
        display.SetSegment(i, segment, true, true);
    }
    display.WriteDisplay();
}

extern "C" {
void SysTick_Handler(void) {
    UpdateDisplay();
    count++;
}

void EXTI1_IRQHandler(void) {
    knob.HandleInterrupt();
}

void EXTI2_IRQHandler(void) {
    knob.HandleInterrupt();
}

void EXTI9_5_IRQHandler(void) {
    knob.HandleInterrupt();
}
}

int main() {
    Init();

    UpdateDisplay();
    while (true);
}
