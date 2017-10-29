#include "gpio_bus.h"

GPIOBus::GPIOBus(Id id)
    : bus_id_(id) {
    gpiox_ = lookup_gpio_typedef(id);
}

bool GPIOBus::operator==(const GPIOBus& other) const {
    return bus_id_ == other.bus_id_;
}

void GPIOBus::Init() {
    RCC_AHB1PeriphClockCmd(lookup_clock_for(bus_id_), ENABLE);
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
        case Id::A: return RCC_AHB1Periph_GPIOA;
        case Id::B: return RCC_AHB1Periph_GPIOB;
        case Id::C: return RCC_AHB1Periph_GPIOC;
        case Id::D: return RCC_AHB1Periph_GPIOD;
        case Id::E: return RCC_AHB1Periph_GPIOE;
        default: return 0;
    }
}

