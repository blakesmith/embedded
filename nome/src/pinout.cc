#include "pinout.h"

// Begin configuration

#ifdef TARGET_BREADBOARD

// StatusLed
#define STATUS_LED_BUS gpiod

static constexpr uint16_t STATUS_OK_LED = 15;
static constexpr uint16_t STATUS_ERROR_LED = 14;
static constexpr uint16_t STATUS_ACTIVITY_LED = 13;

// Pec11 rotary encoder

#define ENCODER_BUS gpiod

static constexpr uint16_t ENCODER_CLOCKWISE = 2;
static constexpr uint16_t ENCODER_COUNTER_CLOCKWISE = 3;
static constexpr uint16_t ENCODER_BUTTON = 6;

// I2C
#define I2C_SCL_BUS gpiob
#define I2C_SDA_BUS gpiob

static constexpr uint16_t I2C_SCL = 6;
static constexpr uint16_t I2C_SDA = 9;
static constexpr I2CBus::Id I2C_ID = I2CBus::Id::ONE;

// DAC

#define DAC_RESET_BUS gpiod
#define DAC_I2S_MCK_BUS gpioc
#define DAC_I2S_CK_BUS gpioc
#define DAC_I2S_SD_BUS gpioc
#define DAC_I2S_WS_BUS gpioa

static constexpr uint16_t DAC_RESET = 4;
static constexpr uint16_t DAC_I2S_MCK = 7;
static constexpr uint16_t DAC_I2S_CK = 10;
static constexpr uint16_t DAC_I2S_SD = 12;
static constexpr uint16_t DAC_I2S_WS = 4;

static constexpr uint8_t DAC_SPI = 3;
// Use define, for preprocessor conditionals below
#define DAC_DMA 1

static constexpr uint32_t DAC_DMA_CHANNEL = 0;
#define DAC_DMA_STREAM 7

/**
 * Don't forget to add a different IRQHandler in the DAC driver
 * if you add a different pinout!
 */
#endif

// End configuration

Pinout::Pinout()
    : gpioa(GPIOBus::Id::A),
      gpiob(GPIOBus::Id::B),
      gpioc(GPIOBus::Id::C),
      gpiod(GPIOBus::Id::D),
      led_ok(STATUS_LED_BUS, STATUS_OK_LED),
      led_error(STATUS_LED_BUS, STATUS_ERROR_LED),
      led_activity(STATUS_LED_BUS, STATUS_ACTIVITY_LED),
      encoder_clockwise(ENCODER_BUS, ENCODER_CLOCKWISE),
      encoder_counter_clockwise(ENCODER_BUS, ENCODER_COUNTER_CLOCKWISE),
      encoder_button(ENCODER_BUS, ENCODER_BUTTON),
      i2c_scl(I2C_SCL_BUS, I2C_SCL),
      i2c_sda(I2C_SDA_BUS, I2C_SDA),
      i2c_bus(I2C_ID, i2c_scl, i2c_sda),
      dac_reset(DAC_RESET_BUS, DAC_RESET),
      dac_i2s_mck(DAC_I2S_MCK_BUS, DAC_I2S_MCK),
      dac_i2s_ck(DAC_I2S_CK_BUS, DAC_I2S_CK),
      dac_i2s_sd(DAC_I2S_SD_BUS, DAC_I2S_SD),
      dac_i2s_ws(DAC_I2S_WS_BUS, DAC_I2S_WS),
      i2s_transmitter(dac_i2s_mck,
                      dac_i2s_ck,
                      dac_i2s_sd,
                      dac_i2s_ws,
                      DAC_SPI,
                      DAC_DMA,
                      DAC_DMA_CHANNEL,
                      DAC_DMA_STREAM)
{}

void Pinout::Init() {
    gpioa.Init();
    gpiob.Init();
    gpioc.Init();
    gpiod.Init();
    i2c_bus.Init();
}
