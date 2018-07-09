#include "scan_matrix.h"

namespace stm32 {

ScanMatrix::ScanMatrix(GPIOPin* rows,
                       GPIOPin* columns,
                       uint8_t row_count,
                       uint8_t column_count) :
    rows_(rows),
    columns_(columns),
    row_count_(row_count),
    column_count_(column_count)
{ }

void ScanMatrix::Init() {
}

}
