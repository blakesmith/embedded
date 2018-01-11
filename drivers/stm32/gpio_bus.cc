#include "drivers/stm32/gpio_bus.h"

#if defined(STM32F411xE) || defined(STM32F413_423xx)
#include "stm32f4xx_rcc.h"
#endif

#ifdef STM32L1XX_MD
#include "stm32l1xx_rcc.h"
#endif

GPIOBus::GPIOBus(Id id)
    : bus_id_(id) {
    gpiox_ = lookup_gpio_typedef(id);
}

bool GPIOBus::operator==(const GPIOBus& other) const {
    return bus_id_ == other.bus_id_;
}

void GPIOBus::Init() {
#ifdef STM32F411xE
    RCC_AHB1PeriphClockCmd(lookup_clock_for(bus_id_), ENABLE);
#endif
#ifdef STM32L1XX_MD
    RCC_AHBPeriphClockCmd(lookup_clock_for(bus_id_), ENABLE);
#endif
}

uint32_t GPIOBus::ReadAll() {
    return gpiox_->IDR;
}

GPIO_TypeDef* GPIOBus::get_gpiox() {
    return gpiox_;
}

GPIO_TypeDef* GPIOBus::lookup_gpio_typedef(Id id) {
    switch (id) {
        case Id::A: return GPIOA;
        case Id::B: return GPIOB;
        case Id::C: return GPIOC;
        case Id::D: return GPIOD;
        case Id::E: return GPIOE;
        default: return nullptr;
    }
}

uint32_t GPIOBus::lookup_clock_for(Id id) {
    switch (id) {
#ifdef STM32F411xE
        case Id::A: return RCC_AHB1Periph_GPIOA;
        case Id::B: return RCC_AHB1Periph_GPIOB;
        case Id::C: return RCC_AHB1Periph_GPIOC;
        case Id::D: return RCC_AHB1Periph_GPIOD;
        case Id::E: return RCC_AHB1Periph_GPIOE;
#endif
#ifdef STM32L1XX_MD
        case Id::A: return RCC_AHBPeriph_GPIOA;
        case Id::B: return RCC_AHBPeriph_GPIOB;
        case Id::C: return RCC_AHBPeriph_GPIOC;
        case Id::D: return RCC_AHBPeriph_GPIOD;
        case Id::E: return RCC_AHBPeriph_GPIOE;
#endif
        default: return 0;
    }
}

