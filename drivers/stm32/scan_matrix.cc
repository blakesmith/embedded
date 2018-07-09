#include "scan_matrix.h"

namespace stm32 {

ScanMatrix::ScanMatrix(GPIOPin* rows,
                       GPIOPin* columns,
                       const uint8_t row_count,
                       const uint8_t column_count) :
    rows_(rows),
    columns_(columns),
    row_count_(row_count),
    column_count_(column_count)
{ }

void ScanMatrix::Init() {
    init_rows();
    init_columns();
}

void ScanMatrix::init_rows() {
    for (unsigned int i = 0; i < row_count_; i++) {
        GPIOPin& row_pin = rows_[i];

        row_pin.set_mode(GPIOPin::Mode::IN);
        row_pin.set_pupd(GPIOPin::PuPd::NONE);
        row_pin.set_speed(GPIOPin::Speed::TWO_MHZ);
        row_pin.Init();
    }
}

void ScanMatrix::init_columns() {
    for (unsigned int i = 0; i < column_count_; i++) {
        GPIOPin& column_pin = columns_[i];

        column_pin.set_mode(GPIOPin::Mode::OUT);
        column_pin.set_pupd(GPIOPin::PuPd::UP);
        column_pin.set_output(GPIOPin::OType::OPEN_DRAIN);
        column_pin.set_speed(GPIOPin::Speed::TWO_MHZ);
        column_pin.Init();
    }
}

bool ScanMatrix::ScanKey(const uint8_t row, const uint8_t column) {
    if ((row > row_count_ - 1) || (column > column_count_ - 1)) {
        return false;
    }

    GPIOPin& row_pin = rows_[row];
    GPIOPin& column_pin = columns_[column];

    column_pin.Set(true);
    bool read = row_pin.Read();
    column_pin.Set(false);
    return read;
}

}
