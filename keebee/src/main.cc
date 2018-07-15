#include "stm32f0xx_hal.h"
#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/scan_matrix.h"
#include "drivers/stm32/status_led.h"

using namespace stm32;

GPIOBus gpioa(GPIOBus::Id::A);
GPIOBus gpiob(GPIOBus::Id::B);

GPIOPin scan_rows[] = {
    GPIOPin(gpiob, 4),
};

GPIOPin scan_columns[] = {
    GPIOPin(gpiob, 6),
};

const uint8_t row_count = sizeof(scan_rows) / sizeof(GPIOPin);
const uint8_t column_count = sizeof(scan_columns) / sizeof(GPIOPin);

GPIOPin st1_ok(gpiob, 0);
GPIOPin st1_err(gpiob, 7);

StatusLed st1(st1_ok, st1_err);

ScanMatrix scan_matrix(scan_rows,
                       scan_columns,
                       row_count,
                       column_count);

static void Init() {
    HAL_Init();

    gpioa.Init();
    gpiob.Init();
    st1.Init();
    scan_matrix.Init();
}

static void scan_and_update() {
    st1.SetOk(scan_matrix.ScanKey(0, 0));
}

int main() {
    Init();

    while (true) {
        scan_and_update();
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}

