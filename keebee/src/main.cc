#include "stm32f0xx_hal.h"
#include "drivers/stm32/dip_switch.h"
#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/scan_matrix.h"
#include "drivers/stm32/status_led.h"

#include "key_pipeline.h"
#include "usb_keyboard.h"

using namespace stm32;

GPIOBus gpioa(GPIOBus::Id::A);
GPIOBus gpiob(GPIOBus::Id::B);

GPIOPin scan_rows[] = {
    GPIOPin(gpiob, 4),
    GPIOPin(gpiob, 5)
};

GPIOPin scan_columns[] = {
    GPIOPin(gpiob, 6),
    GPIOPin(gpiob, 7)
};

static constexpr uint8_t row_count = sizeof(scan_rows) / sizeof(GPIOPin);
static constexpr uint8_t column_count = sizeof(scan_columns) / sizeof(GPIOPin);
static constexpr uint16_t key_count = row_count * column_count;

GPIOPin st1_ok(gpiob, 1);
GPIOPin st1_err(gpiob, 0);

GPIOPin st2_ok(gpioa, 10);
GPIOPin st2_err(gpioa, 9);

StatusLed st1(st1_ok, st1_err);
StatusLed st2(st2_ok, st2_err);

bool key_scans[key_count] = {
};

GPIOPin dip1(gpioa, 3);
GPIOPin dip2(gpioa, 4);

GPIOPin dip_pins[] = {
    dip1, dip2
};

DipSwitch dip_switch(dip_pins, sizeof(dip_pins) / sizeof(GPIOPin));
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
    st1.Init();
    st2.Init();
    dip_switch.Init();
    scan_matrix.Init();
    keyboard.Init();
}

static void scan_and_update() {
    scan_matrix.Scan(key_scans, row_count, column_count);
    st1.SetOk(key_scans[0]);
    st1.SetError(key_scans[1]);
    st2.SetOk(key_scans[2]);
    st2.SetError(key_scans[3]);
}

static void send_keyboard_characters() {
    keyboard.SendReport(
        key_pipeline.MapKeyScans(key_scans, key_count));
}

int main() {
    Init();

    st1.SetOk(true);
    while (true) {
        scan_and_update();
        send_keyboard_characters();
        HAL_Delay(20);
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}

