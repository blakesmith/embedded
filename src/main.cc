#include <stm32f4xx.h>

#define LED_PIN 5
#define LED_ON() 
#define LED_OFF()

int main() {
    /* Enbale GPIOA clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    /* Configure GPIOA pin 5 as output */
    GPIOA->MODER |= (1 << (LED_PIN << 1));
    /* Configure GPIOA pin 5 in max speed */
    GPIOA->OSPEEDR |= (3 << (LED_PIN << 1));

    /* Turn on the LED */
    LED_ON();
}
