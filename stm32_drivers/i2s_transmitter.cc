#include "stm32_drivers/i2s_transmitter.h"

#include "stm32f4xx_rcc.h"

I2STransmitter::I2STransmitter(GPIOPin& i2s_mck_pin,
                               GPIOPin& i2s_ck_pin,
                               GPIOPin& i2s_sd_pin,
                               GPIOPin& i2s_ws_pin,
                               uint8_t i2s_spi,
                               uint8_t i2s_dma,
                               uint32_t i2s_dma_channel,
                               uint8_t i2s_dma_stream)
    : mck_pin(i2s_mck_pin),
      ck_pin(i2s_ck_pin),
      sd_pin(i2s_sd_pin),
      ws_pin(i2s_ws_pin),
      spi(i2s_spi),
      dma(i2s_dma),
      dma_channel(i2s_dma_channel),
      dma_stream(i2s_dma_stream)
{}

DMA_Stream_TypeDef* I2STransmitter::get_dma_stream() {
    switch (dma) {
        case 1:
            switch (dma_stream) {
                case 0: return DMA1_Stream0;
                case 1: return DMA1_Stream1;
                case 2: return DMA1_Stream2;
                case 3: return DMA1_Stream3;
                case 4: return DMA1_Stream4;
                case 5: return DMA1_Stream5;
                case 6: return DMA1_Stream6;
                case 7: return DMA1_Stream7;
                default: return DMA1_Stream0;
            }
        case 2:
            switch (dma_stream) {
                case 0: return DMA2_Stream0;
                case 1: return DMA2_Stream1;
                case 2: return DMA2_Stream2;
                case 3: return DMA2_Stream3;
                case 4: return DMA2_Stream4;
                case 5: return DMA2_Stream5;
                case 6: return DMA2_Stream6;
                case 7: return DMA2_Stream7;
                default: return DMA2_Stream0;
            }
        default: return nullptr;
    }
}

IRQn_Type I2STransmitter::get_irq() {
    switch (dma) {
        case 1:
            switch (dma_stream) {
                case 0: return DMA1_Stream0_IRQn;
                case 1: return DMA1_Stream1_IRQn;
                case 2: return DMA1_Stream2_IRQn;
                case 3: return DMA1_Stream3_IRQn;
                case 4: return DMA1_Stream4_IRQn;
                case 5: return DMA1_Stream5_IRQn;
                case 6: return DMA1_Stream6_IRQn;
                case 7: return DMA1_Stream7_IRQn;
                default: return DMA1_Stream0_IRQn;
            }
        case 2:
            switch (dma_stream) {
                case 0: return DMA2_Stream0_IRQn;
                case 1: return DMA2_Stream1_IRQn;
                case 2: return DMA2_Stream2_IRQn;
                case 3: return DMA2_Stream3_IRQn;
                case 4: return DMA2_Stream4_IRQn;
                case 5: return DMA2_Stream5_IRQn;
                case 6: return DMA2_Stream6_IRQn;
                case 7: return DMA2_Stream7_IRQn;
                default: return DMA2_Stream0_IRQn;
            }
        default: return DMA1_Stream0_IRQn;
    }
}

uint32_t I2STransmitter::get_dma_channel() {
    switch (dma_channel) {
        case 0: return DMA_Channel_0;
        case 1: return DMA_Channel_1;
        case 2: return DMA_Channel_2;
        case 3: return DMA_Channel_3;
        case 4: return DMA_Channel_4;
        case 5: return DMA_Channel_5;
        case 6: return DMA_Channel_6;
        case 7: return DMA_Channel_7;
        default: return DMA_Channel_0;
    }
}

uint32_t I2STransmitter::get_dma_flags() {
    switch (dma_stream) {
        case 0: return DMA_FLAG_TCIF0;
        case 1: return DMA_FLAG_TCIF1;
        case 2: return DMA_FLAG_TCIF2;
        case 3: return DMA_FLAG_TCIF3;
        case 4: return DMA_FLAG_TCIF4;
        case 5: return DMA_FLAG_TCIF5;
        case 6: return DMA_FLAG_TCIF6;
        case 7: return DMA_FLAG_TCIF7;
        default: return 0;
    }
}

uint32_t I2STransmitter::get_spi_clock() {
    switch (spi) {
        case 2: return RCC_APB1Periph_SPI2;
        case 3: return RCC_APB1Periph_SPI3;
        default: return 0;
    }
}

SPI_TypeDef* I2STransmitter::get_spi() {
    switch (spi) {
        case 2: return SPI2;
        case 3: return SPI3;
        default: return nullptr;
    }
}

