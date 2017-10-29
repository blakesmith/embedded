#ifndef GPIO_BUS_H_
#define GPIO_BUS_H_

class GPIOBus {
public:
    enum class BusId {
        A,
        B,
        C,
        D,
        E
    };
    
    GPIOBus(BusId id);
    ~GPIOBus() = default;
    
    void Init();
    
private:
    BusId bus_id_;
    GPIO_TypeDef* gpiox_;

    GPIO_TypeDef* lookup_gpio_typedef(BusId id);
    uint32_t lookup_clock_for(BusId id);
};

#endif
