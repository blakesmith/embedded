#include "gpio_bus.h"

GPIOBus::GPIOBus(BusId id)
    : bus_id_(id) {
    gpiox_ = lookup_gpio_typedef(id);
}

GPIO_TypeDef* GPIOBus::lookup_gpio_typedef(BusId id) {
    switch (id) {
        case BusId::A: return GPIOA;
        case BusId::B: return GPIOB;
        case BusId::C: return GPIOC;
        case BusId::D: return GPIOD;
        case BusId::E: return GPIOE;
        default: return nullptr;
    }
}

uint32_t GPIOBus::lookup_clock_for(BusId id) {
    switch (id) {
        case BusId::A: return RCC_AHB1Periph_GPIOA;
        case BusId::B: return RCC_AHB1Periph_GPIOB;
        case BusId::C: return RCC_AHB1Periph_GPIOC;
        case BusId::D: return RCC_AHB1Periph_GPIOD;
        case BusId::E: return RCC_AHB1Periph_GPIOE;
        default: return 0;
    }
}

void GPIOBus::Init() {
    RCC_AHB1PeriphClockCmd(lookup_clock_for(bus_id_), ENABLE);
}

