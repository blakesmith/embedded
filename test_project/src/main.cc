#include <stm32f4xx.h>
#include <cstddef>

#include "drivers/stm32/gpio_bus.h"
#include "drivers/stm32/i2c_bus.h"
#include "drivers/stm32/ht16K33_display.h"
#include "drivers/stm32/as1115_display.h"
#include "drivers/stm32/status_led.h"

GPIOBus gpiob(GPIOBus::Id::B);
GPIOBus gpiod(GPIOBus::Id::D);

GPIOPin scl_pin(gpiob, 6);
GPIOPin sda_pin(gpiob, 9);

GPIOPin ok_led(gpiod, 15);
GPIOPin error_led(gpiod, 14);
GPIOPin activity_led(gpiod, 13);

StatusLed status_led(ok_led, error_led, activity_led);

I2CBus i2c(I2CBus::Id::ONE, scl_pin, sda_pin);
AS1115Display display_as1115(i2c, 5);
HT16K33Display display_ht16k(i2c, 5);

Display7Seg* displays[] = {
    &display_ht16k,
    &display_as1115
};

static size_t display_count = sizeof(displays) / sizeof(Display7Seg*);

volatile uint32_t count = 0;

static void Init() {
    gpiob.Init();
    gpiod.Init();

    status_led.Init();
    i2c.Init();
    for (unsigned int i = 0; i < display_count; i++) {
        displays[i]->Init();
    }
}

static void CountTest(Display7Seg* display) {
    display->Clear();
    display->ToggleColon(true);
    display->SetNumber(count % 10000);
    display->WriteDisplay();
}

static void SegmentTest(Display7Seg* display) {
    display->Clear();
    for (int i = 0; i < 5; i++) {
        display->SetSegment(i, count % 7, true, true);
    }
    display->WriteDisplay();
}

static void UpdateDisplay() {
    for (unsigned int i = 0; i < display_count; i++) {
//        CountTest(displays[i]);
        SegmentTest(displays[i]);
    }
}

int main() {
    Init();

    status_led.SetOk(true);
    while (true) {
        UpdateDisplay();
        for (int i = 0; i < 1280000; i++);
        count++;
    }
}

extern "C" {
void __cxa_pure_virtual() {
}
}
