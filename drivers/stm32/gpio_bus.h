#ifndef GPIO_BUS_H_
#define GPIO_BUS_H_

#if defined(STM32F411xE) || defined(STM32F413_423xx)
#include "stm32f4xx_gpio.h"
#endif

#ifdef STM32L1XX_MD
#include "stm32l1xx_gpio.h"
#endif

#ifdef STM32F042x6
#include "stm32f0xx_hal_gpio.h"
#endif

#include <cstdint>

class GPIOBus {
public:
    enum class Id {
        A,
        B,
        C,
        D,
        E
    };
    
    GPIOBus(Id id);
    ~GPIOBus() = default;
    
    void Init();
    uint32_t ReadAll();
    GPIO_TypeDef* get_gpiox();

    bool operator==(const GPIOBus& other) const;
    
private:
    Id bus_id_;
    GPIO_TypeDef* gpiox_;

    GPIO_TypeDef* lookup_gpio_typedef(Id id);
    uint32_t lookup_clock_for(Id id);
#ifdef STM32F042x6
    void hal_enable_clock_for(Id id);
#endif
};

#endif
