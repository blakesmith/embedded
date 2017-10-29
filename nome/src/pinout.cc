#include "pinout.h"

// Begin configuration

// StatusLed
#define STATUS_LED_BUS gpiod

static constexpr uint16_t STATUS_OK_LED = 15;
static constexpr uint16_t STATUS_ERROR_LED = 14;
static constexpr uint16_t STATUS_ACTIVITY_LED = 13;

// I2C
#define I2C_SCL_BUS gpioa
#define I2C_SDA_BUS gpioc

static constexpr uint16_t I2C_SCL = 8;
static constexpr uint16_t I2C_SDA = 9;
static constexpr I2CBus::Id I2C_ID = I2CBus::Id::THREE;

// End configuration

Pinout::Pinout()
    : gpioa(GPIOBus::Id::A),
      gpioc(GPIOBus::Id::C),
      gpiod(GPIOBus::Id::D),
      led_ok(STATUS_LED_BUS, STATUS_OK_LED),
      led_error(STATUS_LED_BUS, STATUS_ERROR_LED),
      led_activity(STATUS_LED_BUS, STATUS_ACTIVITY_LED),
      i2c_scl(I2C_SCL_BUS, I2C_SCL),
      i2c_sda(I2C_SDA_BUS, I2C_SDA),
      i2c_bus(I2C_ID, i2c_scl, i2c_sda)
{}

void Pinout::Init() {
    gpioa.Init();
    gpioc.Init();
    gpiod.Init();
    i2c_bus.Init();
}
