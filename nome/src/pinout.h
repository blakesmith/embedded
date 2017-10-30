#ifndef PINOUT_H_
#define PINOUT_H_

#include "gpio_pin.h"
#include "i2c_bus.h"
#include "i2s_transmitter.h"
// Begin configuration

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

// End configuration

struct Pinout {
    GPIOBus gpioa;
    GPIOBus gpiob;
    GPIOBus gpioc;
    GPIOBus gpiod;

    // StatusLed
    GPIOPin led_ok;
    GPIOPin led_error;
    GPIOPin led_activity;

    // Pec11 rotary encoder
    GPIOPin encoder_clockwise;
    GPIOPin encoder_counter_clockwise;
    GPIOPin encoder_button;

    // I2C, Display & DAC
    GPIOPin i2c_scl;
    GPIOPin i2c_sda;
    I2CBus i2c_bus;

    // DAC
    GPIOPin dac_reset;
    
    GPIOPin dac_i2s_mck;
    GPIOPin dac_i2s_ck;
    GPIOPin dac_i2s_sd;
    GPIOPin dac_i2s_ws;

    I2STransmitter i2s_transmitter;

    Pinout();
    void Init();
};

#if DAC_DMA == 1

#if DAC_DMA_STREAM == 0
#define DAC_IRQ_HANDLER DMA1_Stream0_IRQHandler

#elif DAC_DMA_STREAM == 1
#define DAC_IRQ_HANDLER DMA1_Stream1_IRQHandler

#elif DAC_DMA_STREAM == 2
#define DAC_IRQ_HANDLER DMA1_Stream2_IRQHandler

#elif DAC_DMA_STREAM == 3
#define DAC_IRQ_HANDLER DMA1_Stream3_IRQHandler

#elif DAC_DMA_STREAM == 4
#define DAC_IRQ_HANDLER DMA1_Stream4_IRQHandler

#elif DAC_DMA_STREAM == 5
#define DAC_IRQ_HANDLER DMA1_Stream5_IRQHandler

#elif DAC_DMA_STREAM == 6
#define DAC_IRQ_HANDLER DMA1_Stream6_IRQHandler

#elif DAC_DMA_STREAM == 7
#define DAC_IRQ_HANDLER DMA1_Stream7_IRQHandler
#endif
#endif

#if DAC_DMA == 2

#if DAC_DMA_STREAM == 0
#define DAC_IRQ_HANDLER DMA2_Stream0_IRQHandler

#elif DAC_DMA_STREAM == 1
#define DAC_IRQ_HANDLER DMA2_Stream1_IRQHandler

#elif DAC_DMA_STREAM == 2
#define DAC_IRQ_HANDLER DMA2_Stream2_IRQHandler

#elif DAC_DMA_STREAM == 3
#define DAC_IRQ_HANDLER DMA2_Stream3_IRQHandler

#elif DAC_DMA_STREAM == 4
#define DAC_IRQ_HANDLER DMA2_Stream4_IRQHandler

#elif DAC_DMA_STREAM == 5
#define DAC_IRQ_HANDLER DMA2_Stream5_IRQHandler

#elif DAC_DMA_STREAM == 6
#define DAC_IRQ_HANDLER DMA2_Stream6_IRQHandler

#elif DAC_DMA_STREAM == 7
#define DAC_IRQ_HANDLER DMA2_Stream7_IRQHandler

#endif
#endif


#endif // PINOUT_H_
