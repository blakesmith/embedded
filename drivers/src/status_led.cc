#include "status_led.h"

#include "stm32f4xx_gpio.h"

static constexpr uint16_t GPIO_OK_LED = GPIO_Pin_15;
static constexpr uint16_t GPIO_ERROR_LED = GPIO_Pin_14;

static constexpr uint32_t GPIO_CLK = RCC_AHB1Periph_GPIOD;

static GPIO_TypeDef *GPIOx_OK = GPIOD;
static GPIO_TypeDef *GPIOx_ERROR = GPIOD;

void StatusLed::Init() {
    GPIO_InitTypeDef gpio_init;
    
    RCC_AHB1PeriphClockCmd(GPIO_CLK, ENABLE);
    
    gpio_init.GPIO_Pin = GPIO_OK_LED;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOx_OK, &gpio_init);

    gpio_init.GPIO_Pin = GPIO_ERROR_LED;
    GPIO_Init(GPIOx_ERROR, &gpio_init);
}

void StatusLed::SetOk(bool on) {
    uint16_t toggle = on ? 0xFFFF : 0;
    GPIOx_OK->ODR = GPIOx_OK->ODR | (GPIO_OK_LED & toggle);
}

void StatusLed::SetError(bool on) {
    uint16_t toggle = on ? 0xFFFF : 0;
    GPIOx_ERROR->ODR = GPIOx_ERROR->ODR | (GPIO_ERROR_LED & toggle);
}

void StatusLed::ToggleOk() {
    GPIOx_OK->ODR ^= GPIO_OK_LED;
}

void StatusLed::ToggleError() {
    GPIOx_ERROR->ODR ^= GPIO_ERROR_LED;
}
