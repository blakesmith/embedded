#include "gpio_pin.h"

GPIOPin::GPIOPin(GPIOBus& bus,
                 uint16_t pin)
    : bus_(bus),
      mode_(Mode::NONE),
      otype_(OType::NONE),
      pupd_(PuPd::NONE),
      speed_(Speed::NONE) {
    pin_number_ = lookup_pin_number_for(pin);
}

uint32_t GPIOPin::lookup_pin_number_for(uint16_t pin) {
    switch (pin) {
        case 1: return GPIO_Pin_1;
        case 2: return GPIO_Pin_2;
        case 3: return GPIO_Pin_3;
        case 4: return GPIO_Pin_4;
        case 5: return GPIO_Pin_5;
        case 6: return GPIO_Pin_6;
        case 7: return GPIO_Pin_7;
        case 8: return GPIO_Pin_8;
        case 9: return GPIO_Pin_9;
        case 10: return GPIO_Pin_10;
        case 11: return GPIO_Pin_11;
        case 12: return GPIO_Pin_12;
        case 13: return GPIO_Pin_13;
        case 14: return GPIO_Pin_14;
        case 15: return GPIO_Pin_15;
        default: return 0;
    }
}

GPIOMode_TypeDef GPIOPin::lookup_mode_for(Mode mode) {
    switch (mode) {
        case Mode::IN: return GPIO_Mode_IN;
        case Mode::OUT: return GPIO_Mode_OUT;
        default: return GPIO_Mode_IN;
    }
}

GPIOOType_TypeDef GPIOPin::lookup_output_for(OType otype) {
    switch (otype) {
        case OType::PUSH_PULL: return GPIO_OType_PP;
        case OType::OPEN_DRAIN: return GPIO_OType_OD;
        default: return GPIO_OType_PP;
    }
}

GPIOPuPd_TypeDef GPIOPin::lookup_push_pull_for(PuPd pupd) {
    switch (pupd) {
        case PuPd::UP: return GPIO_PuPd_UP;
        case PuPd::DOWN: return GPIO_PuPd_DOWN;
        default: return GPIO_PuPd_UP;
    }
}

GPIOSpeed_TypeDef GPIOPin::lookup_speed_for(Speed speed) {
    switch (speed) {
        case Speed::TWO_MHZ: return GPIO_Speed_2MHz;
        case Speed::FIFTY_MHZ: return GPIO_Speed_50MHz;
        default: return GPIO_Speed_50MHz;
    }
}

void GPIOPin::Init() {
    GPIO_InitTypeDef gpio_init;

    GPIO_StructInit(&gpio_init);

    gpio_init.GPIO_Pin = pin_number_;
    gpio_init.GPIO_Mode = lookup_mode_for(mode_);
    gpio_init.GPIO_OType = lookup_output_for(otype_);
    gpio_init.GPIO_Speed = lookup_speed_for(speed_);
    gpio_init.GPIO_PuPd = lookup_push_pull_for(pupd_);

    GPIO_Init(bus_.get_gpiox(), &gpio_init);
}

void GPIOPin::Set(bool on) {
    uint16_t toggle = on ? 0xFFFF : 0;
    bus_.get_gpiox()->ODR = bus_.get_gpiox()->ODR | (pin_number_ & toggle);
}

void GPIOPin::Toggle() {
    bus_.get_gpiox()->ODR ^= pin_number_;
}

void GPIOPin::set_mode(Mode mode) {
    this->mode_ = mode;
}

void GPIOPin::set_output(OType otype) {
    this->otype_ = otype;
}

void GPIOPin::set_pupd(PuPd pupd) {
    this->pupd_ = pupd;
}

void GPIOPin::set_speed(Speed speed) {
    this->speed_ = speed;
}
