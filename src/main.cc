#include <stm32f4xx.h>
#include <cstddef>

GPIO_InitTypeDef GPIO_LED;

static const uint32_t states[] = {
    GPIO_Pin_12,
    GPIO_Pin_12 | GPIO_Pin_13,
    GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14,
    GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
    GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
    GPIO_Pin_14 | GPIO_Pin_15,
    GPIO_Pin_15,
    0,
    GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
    0,
    GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
    0,
    GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,
    0
};

static const size_t n_states = sizeof(states) / sizeof(uint32_t);
static size_t current_state = 0;

void Init() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_LED.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_LED.GPIO_OType = GPIO_OType_PP;
    GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_LED);

    uint32_t rc = SysTick_Config(SystemCoreClock / 10);
    if (rc != 0) {
        GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
    }
}

void AdvanceLedState() {
    uint32_t pins = states[current_state];
    GPIOD->ODR = pins;
    current_state = (current_state + 1) % n_states;
}

extern "C" {
void SysTick_Handler(void) {
    AdvanceLedState();
}
}

int main() {
    Init();

    while (true);
}
