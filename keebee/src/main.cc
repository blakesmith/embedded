#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/scan_matrix.h"

using namespace stm32;

GPIOBus gpioa(GPIOBus::Id::A);
GPIOBus gpiob(GPIOBus::Id::B);

GPIOPin scan_rows[] = {
    GPIOPin(gpiob, 3),
    GPIOPin(gpiob, 4)
};

GPIOPin scan_columns[] = {
    GPIOPin(gpioa, 0),
    GPIOPin(gpioa, 1),
    GPIOPin(gpioa, 2),
    GPIOPin(gpioa, 3),
};

ScanMatrix scan_matrix(scan_rows,
                       scan_columns,
                       sizeof(scan_rows) / sizeof(GPIOPin),
                       sizeof(scan_columns) / sizeof(GPIOPin));

static void Init() {
    scan_matrix.Init();
}

int main() {
    Init();

    while (true);
}

extern "C" {
void __cxa_pure_virtual() {
}
}

