#ifndef SCAN_MATRIX_H_
#define SCAN_MATRIX_H_

#include "gpio_pin.h"

namespace stm32 {

class ScanMatrix {
public:
    ScanMatrix(GPIOPin* rows,
               GPIOPin* columns,
               uint8_t row_count,
               uint8_t column_count);
    ~ScanMatrix() = default;

    void Init();

private:
    GPIOPin* rows_;
    GPIOPin* columns_;

    uint8_t row_count_;
    uint8_t column_count_;
};

}

#endif
