#include "pinout.h"

static constexpr uint16_t STATUS_OK_LED = 15;
static constexpr uint16_t STATUS_ERROR_LED = 14;
static constexpr uint16_t STATUS_ACTIVITY_LED = 13;

Pinout::Pinout()
    : gpiod(GPIOBus::Id::D),
      led_ok(gpiod, STATUS_OK_LED),
      led_error(gpiod, STATUS_ERROR_LED),
      led_activity(gpiod, STATUS_ACTIVITY_LED)
{}

void Pinout::Init() {
    gpiod.Init();
}
