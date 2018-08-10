#include "stm32f0xx_hal.h"
#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/scan_matrix.h"
#include "drivers/stm32/status_led.h"

#include "layout.h"
#include "key_pipeline.h"
#include "usb_keyboard.h"

using namespace stm32;

GPIOBus gpioa(GPIOBus::Id::A);
GPIOBus gpiob(GPIOBus::Id::B);

GPIOPin scan_rows[] = {
    GPIOPin(gpiob, 3),
    GPIOPin(gpiob, 4),
    GPIOPin(gpiob, 5),
    GPIOPin(gpiob, 6),
    GPIOPin(gpiob, 7),
};

GPIOPin scan_columns[] = {
    GPIOPin(gpioa, 0),
    GPIOPin(gpioa, 1),
    GPIOPin(gpioa, 2),
    GPIOPin(gpioa, 3),
    GPIOPin(gpioa, 4),
    GPIOPin(gpioa, 5),
    GPIOPin(gpioa, 6),
    GPIOPin(gpioa, 7),
    GPIOPin(gpiob, 0),
    GPIOPin(gpiob, 1),
    GPIOPin(gpioa, 8),
    GPIOPin(gpioa, 9),
    GPIOPin(gpioa, 10),
    GPIOPin(gpioa, 15),
};

static constexpr uint8_t row_count = sizeof(scan_rows) / sizeof(GPIOPin);
static constexpr uint8_t column_count = sizeof(scan_columns) / sizeof(GPIOPin);
static constexpr uint16_t key_count = row_count * column_count;

GPIOPin status_ok(gpiob, 8);
StatusLed status_led(status_ok, status_ok);

bool key_scans[key_count] = {
};

ScanMatrix scan_matrix(scan_rows,
                       scan_columns,
                       row_count,
                       column_count);
USBKeyboard keyboard;
KeyPipeline key_pipeline;

static void Init() {
    HAL_Init();

    gpioa.Init();
    gpiob.Init();
    scan_matrix.Init();
    keyboard.Init();
    status_led.Init();
}

static void scan_and_update() {
    scan_matrix.Scan(key_scans, row_count, column_count);
    keyboard.SendReport(
        key_pipeline.MapKeyScans(key_scans, key_count));
}

int main() {
    Init();

    status_led.SetOk(true);
    while (true) {
        scan_and_update();
        HAL_Delay(20);
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}

