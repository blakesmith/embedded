#ifndef HT16K33_DISPLAY_H_
#define HT16K33_DISPLAY_H_

#include "display_7seg.h"

class HT16K33Display : public Display7Seg {
public:
    HT16K33Display(I2CBus& i2c_bus,
                   uint8_t device_address);
    HT16K33Display(I2CBus& i2c_bus);
    ~HT16K33Display() = default;

    virtual void Init();
    virtual void SetBrightness(uint8_t brightness);

private:
    void enable_oscillator();
    void set_blink_rate(uint8_t rate);
};

#endif
