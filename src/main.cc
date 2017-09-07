#include <stm32f4xx.h>
#include <cstddef>

#define DELAY_AMOUNT 200000

GPIO_InitTypeDef GPIO_LED;

void Init() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_LED.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_LED.GPIO_OType = GPIO_OType_PP;
    GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_LED);
}

void Delay(__IO uint32_t count) {
    while (count--);
}

void BlinkLed(uint16_t pin) {
    GPIO_WriteBit(GPIOD, pin, Bit_SET);
    Delay(DELAY_AMOUNT);
    GPIO_WriteBit(GPIOD, pin, Bit_RESET);
}

int main() {
    Init();

    static const uint16_t pins[] = {
        GPIO_Pin_12,
        GPIO_Pin_13,
        GPIO_Pin_14,
        GPIO_Pin_15
    };


    while (true) {
        for (size_t i = 0; i < sizeof(pins) / sizeof(uint16_t); i++) {
            BlinkLed(pins[i]);
        }
    }
}
