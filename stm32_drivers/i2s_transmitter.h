#ifndef I2S_TRANSMITTER_H_
#define I2S_TRANSMITTER_H_

#include "gpio_pin.h"

#include "stm32f4xx_dma.h"
#include "stm32f4xx_spi.h"

struct I2STransmitter {
    I2STransmitter(GPIOPin& mck_pin,
                   GPIOPin& ck_pin,
                   GPIOPin& sd_pin,
                   GPIOPin& ws_pin,
                   uint8_t spi,
                   uint8_t dma,
                   uint32_t dma_channel,
                   uint8_t dma_stream);
    
    GPIOPin& mck_pin;
    GPIOPin& ck_pin;
    GPIOPin& sd_pin;
    GPIOPin& ws_pin;

    uint8_t spi;
    uint8_t dma;
    uint32_t dma_channel;
    uint8_t dma_stream;

    DMA_Stream_TypeDef* get_dma_stream();
    uint32_t get_dma_channel();
    uint32_t get_dma_flags();
    IRQn_Type get_irq();
    
    SPI_TypeDef* get_spi();
    uint32_t get_spi_clock();
    
};

#endif
