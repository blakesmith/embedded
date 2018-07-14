#include "drivers/stm32/gpio_pin.h"

GPIOPin::GPIOPin(GPIOBus& bus,
                 uint16_t pin)
    : bus_(bus),
      mode_(Mode::NONE),
      otype_(OType::NONE),
      pupd_(PuPd::NONE),
      speed_(Speed::NONE),
      af_(Af::NONE) {
    pin_number_ = lookup_pin_number_for(pin);
    pin_source_ = lookup_pin_source_for(pin);
}

void GPIOPin::Init() {
#if defined(STM32_STD_PERIPH)
    std_periph_init();
#elif defined(STM32_HAL)
    hal_init();
#else
#error "You need to define a processor that either uses the STM32 standard peripheral library, or the HAL library"
#endif
}

uint32_t GPIOPin::lookup_pin_number_for(uint16_t pin) {
#if defined(STM32_STD_PERIPH)    
    switch (pin) {
        case 0: return GPIO_Pin_0;
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
#else
    switch (pin) {
        case 0: return GPIO_PIN_0;
        case 1: return GPIO_PIN_1;
        case 2: return GPIO_PIN_2;
        case 3: return GPIO_PIN_3;
        case 4: return GPIO_PIN_4;
        case 5: return GPIO_PIN_5;
        case 6: return GPIO_PIN_6;
        case 7: return GPIO_PIN_7;
        case 8: return GPIO_PIN_8;
        case 9: return GPIO_PIN_9;
        case 10: return GPIO_PIN_10;
        case 11: return GPIO_PIN_11;
        case 12: return GPIO_PIN_12;
        case 13: return GPIO_PIN_13;
        case 14: return GPIO_PIN_14;
        case 15: return GPIO_PIN_15;
        default: return 0;
    }
#endif
}

uint16_t GPIOPin::lookup_pin_source_for(uint16_t pin) {
#if defined(STM32_STD_PERIPH)
    switch (pin) {
        case 0: return GPIO_PinSource0;
        case 1: return GPIO_PinSource1;
        case 2: return GPIO_PinSource2;
        case 3: return GPIO_PinSource3;
        case 4: return GPIO_PinSource4;
        case 5: return GPIO_PinSource5;
        case 6: return GPIO_PinSource6;
        case 7: return GPIO_PinSource7;
        case 8: return GPIO_PinSource8;
        case 9: return GPIO_PinSource9;
        case 10: return GPIO_PinSource10;
        case 11: return GPIO_PinSource11;
        case 12: return GPIO_PinSource12;
        case 13: return GPIO_PinSource13;
        case 14: return GPIO_PinSource14;
        case 15: return GPIO_PinSource15;
        default: return 0;
    }
#else
    return 0; // PinSource not used with HAL driver
#endif
}

// Start standard peripheral init
#if defined(STM32_STD_PERIPH)
/**
 * Init function for the older, standard peripheral library drivers.
 */
void GPIOPin::std_periph_init() {
    GPIO_InitTypeDef gpio_init;

    if (af_ != Af::NONE) {
        GPIO_PinAFConfig(bus_.get_gpiox(),
                         pin_source_,
                         lookup_alternative_function_for(af_));
    }

    GPIO_StructInit(&gpio_init);

    gpio_init.GPIO_Pin = pin_number_;
    gpio_init.GPIO_Mode = lookup_mode_for(mode_);
    gpio_init.GPIO_OType = lookup_output_for(otype_);
    gpio_init.GPIO_Speed = lookup_speed_for(speed_);
    gpio_init.GPIO_PuPd = lookup_push_pull_for(pupd_);
    
    GPIO_Init(bus_.get_gpiox(), &gpio_init);
}

uint8_t GPIOPin::lookup_alternative_function_for(Af af) {
    switch (af) {
        case Af::I2C_1: return GPIO_AF_I2C1;
        case Af::I2C_2: return GPIO_AF_I2C2;
#if defined(STM32F411xE) || defined(STM32F413_423xx)
        case Af::I2C_3: return GPIO_AF_I2C3;
#endif
        case Af::SPI_1: return GPIO_AF_SPI1;
        case Af::SPI_2: return GPIO_AF_SPI2;
        case Af::SPI_3: return GPIO_AF_SPI3;
        default: return 0;
    }
}

GPIOMode_TypeDef GPIOPin::lookup_mode_for(Mode mode) {
    switch (mode) {
        case Mode::IN: return GPIO_Mode_IN;
        case Mode::OUT: return GPIO_Mode_OUT;
        case Mode::AF: return GPIO_Mode_AF;
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
        default: return GPIO_PuPd_NOPULL;
    }
}

GPIOSpeed_TypeDef GPIOPin::lookup_speed_for(Speed speed) {
    switch (speed) {
        case Speed::TWO_MHZ: return GPIO_Speed_2MHz;
#if defined(STM32F411xE) || defined(STM32F413_423xx)
        case Speed::FIFTY_MHZ: return GPIO_Speed_50MHz;
#endif
        default: return GPIO_Speed_2MHz;
    }
}

#endif // End standard peripheral init

#ifdef STM32_HAL

void GPIOPin::hal_init() {
    GPIO_InitTypeDef gpio_init;

    if (af_ != Af::NONE) {
        gpio_init.Alternate = hal_lookup_alternative_function_for(af_);
    }
    gpio_init.Pin = pin_number_;
    gpio_init.Mode = hal_lookup_mode_output_for(mode_, otype_);
    gpio_init.Pull = hal_lookup_push_pull_for(pupd_);
    gpio_init.Speed = hal_lookup_speed_for(speed_);

    HAL_GPIO_Init(bus_.get_gpiox(), &gpio_init);
}

uint8_t GPIOPin::hal_lookup_alternative_function_for(Af af) {
    switch (af) {
        case Af::I2C_1:   return GPIO_AF1_I2C1;
        case Af::I2C_3:   return GPIO_AF3_I2C1;
        case Af::I2C_4:   return GPIO_AF4_I2C1;
        case Af::I2C_5:   return GPIO_AF5_I2C1;
        case Af::I2C_5_2: return GPIO_AF5_I2C2;
        case Af::SPI_0:   return GPIO_AF0_SPI1;
        case Af::SPI_0_2: return GPIO_AF0_SPI2;
        case Af::SPI_5_2: return GPIO_AF5_SPI2;
        default: return 0;
    }
}


uint32_t GPIOPin::hal_lookup_push_pull_for(PuPd pupd) {
    switch (pupd) {
        case PuPd::UP: return GPIO_PULLUP;
        case PuPd::DOWN: return GPIO_PULLDOWN;
        default: return GPIO_NOPULL;
    }
}

uint32_t GPIOPin::hal_lookup_speed_for(Speed speed) {
    switch (speed) {
        case Speed::TWO_MHZ: return GPIO_SPEED_FREQ_LOW;
        case Speed::FIFTY_MHZ: return GPIO_SPEED_FREQ_HIGH;
        default: return GPIO_SPEED_FREQ_LOW;
    }
}

uint32_t GPIOPin::hal_lookup_mode_output_for(Mode mode, OType otype) {
    if (mode == Mode::OUT && otype == OType::PUSH_PULL) {
        return GPIO_MODE_OUTPUT_PP;
    } else if (mode == Mode::OUT && otype == OType::OPEN_DRAIN) {
        return GPIO_MODE_OUTPUT_OD;
    } else if (mode == Mode::IN) {
        return GPIO_MODE_INPUT;
    } else if (mode == Mode::AF && otype == OType::PUSH_PULL) {
        return GPIO_MODE_AF_PP;
    } else if (mode == Mode::AF && otype == OType::OPEN_DRAIN) {
        return GPIO_MODE_AF_OD;
    } else {
        return 0;
    }
}

#endif // End hal init functions

void GPIOPin::Set(bool on) {
    if (on) {
        bus_.get_gpiox()->BSRR = pin_number_;
    } else {
        bus_.get_gpiox()->BSRR = ((uint32_t)pin_number_ << 16);
    }
}

bool GPIOPin::Read() {
#if defined(STM32_HAL)
    const uint32_t reset = GPIO_PIN_RESET;
#else
    const uint32_t reset = Bit_RESET;
#endif
    return (bus_.get_gpiox()->IDR & pin_number_) != reset;
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

void GPIOPin::set_alternative_function(Af af) {
    this->af_ = af;
}

GPIOBus& GPIOPin::get_bus() {
    return bus_;
}

uint32_t GPIOPin::get_pin_number() {
    return pin_number_;
}
