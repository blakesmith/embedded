#ifndef AS1115_DISPLAY_H_
#define AS1115_DISPLAY_H_

#include "display_7seg.h"

class AS1115Display : public Display7Seg {
public:
    AS1115Display(I2CBus& i2c_bus,
                  uint8_t n_digits,
                  uint8_t device_address);
    AS1115Display(I2CBus& i2c_bus,
                  uint8_t n_digits);
    ~AS1115Display() = default;

    void Init();
    void SetBrightness(uint8_t brightness);
    void SimpleWrite(uint8_t digit);

private:
    void wakeup();
    void disable_decode();
    void set_scan_limit(uint8_t limit);
};

#endif
