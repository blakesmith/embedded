#ifndef SCAN_MATRIX_H_
#define SCAN_MATRIX_H_

#include "gpio_pin.h"

namespace stm32 {

class ScanMatrix {
public:
    ScanMatrix(GPIOPin* rows,
               GPIOPin* columns,
               const uint8_t row_count,
               const uint8_t column_count);
    ~ScanMatrix() = default;

    void Init();

    int Scan(bool** key_scans, const size_t row_len, const size_t column_len);
    bool ScanKey(const uint8_t row,
                 const uint8_t column);

private:
    GPIOPin* rows_;
    GPIOPin* columns_;

    uint8_t row_count_;
    uint8_t column_count_;

    void init_rows();
    void init_columns();
};

}

#endif
