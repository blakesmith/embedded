#include "pinout.h"

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
