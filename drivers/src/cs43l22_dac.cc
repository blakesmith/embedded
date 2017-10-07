#include "cs43l22_dac.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "i2c_common.h"

#include <cstring>

// Static instance, for the IRQ handler
CS43L22Dac *CS43L22Dac::global_dac_;

// I2C
static I2C_TypeDef *I2Cx = I2C1;
static GPIO_TypeDef *GPIOx_I2C = GPIOB;

static constexpr uint32_t RCC_I2C_PERIPH = RCC_APB1Periph_I2C1;
static constexpr uint32_t RCC_GPIO_I2C_PERIPH = RCC_AHB1Periph_GPIOB;

static constexpr uint16_t GPIO_PS_I2C_SCL = GPIO_PinSource6;
static constexpr uint16_t GPIO_PS_I2C_SDA = GPIO_PinSource9;

static constexpr uint16_t GPIO_PIN_I2C_SCL = GPIO_Pin_6;
static constexpr uint16_t GPIO_PIN_I2C_SDA = GPIO_Pin_9;

static constexpr uint8_t GPIO_I2C_AFx = GPIO_AF_I2C1;

// I2S
static SPI_TypeDef *SPI_I2S = SPI3;
static GPIO_TypeDef *GPIO1_I2S = GPIOA;
static GPIO_TypeDef *GPIO2_I2S = GPIOC;
static constexpr uint32_t RCC_GPIO_I2S_PERIPH = RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC;
static constexpr uint32_t RCC_SPI_I2S_CLOCK = RCC_APB1Periph_SPI3;

static constexpr uint16_t GPIO_PS_I2S_MCK = GPIO_PinSource7;
static constexpr uint16_t GPIO_PS_I2S_CK = GPIO_PinSource10;
static constexpr uint16_t GPIO_PS_I2S_SD = GPIO_PinSource12;
static constexpr uint16_t GPIO_PS_I2S_WS = GPIO_PinSource4;

static constexpr uint16_t GPIO_PIN_I2S_MCK = GPIO_Pin_7;
static constexpr uint16_t GPIO_PIN_I2S_CK = GPIO_Pin_10;
static constexpr uint16_t GPIO_PIN_I2S_SD = GPIO_Pin_12;
static constexpr uint16_t GPIO_PIN_I2S_WS = GPIO_Pin_4;

static constexpr uint8_t GPIO_I2S_TX_AFx = GPIO_AF_SPI3;
static constexpr uint32_t I2S_DMA_TX_CHANNEL = DMA_Channel_0;
static DMA_Stream_TypeDef *I2S_DMA_TX_STREAM = DMA1_Stream7;
static constexpr uint32_t I2S_DMA_TX_TC_FLAG = DMA_FLAG_TCIF7;
static IRQn_Type I2S_TX_DMA_IRQ = DMA1_Stream7_IRQn;

void CS43L22Dac::Init(uint8_t volume, DacFillCallback fill_callback) {
    global_dac_ = this;
    fill_callback_ = fill_callback;

    memset(tx_dma_buf_, 0, DAC_BUF_SIZE);
    
    init_gpio();
    init_i2c();
    init_i2s();
    
    // Hold power off
    write_register(CS_REG_POW_CTL1, 0x01);
    
    // Set the output device to auto detect, headphone or speaker depending on if the headphones are plugged in
    write_register(CS_REG_POW_CTL2, CS_OUT_AUTO);

    // Configure the clocking control to AUTO, and enable MCLKDIV2
    write_register(CS_REG_CLOCKING_CTL, CS_CLOCKING_AUTO);

    // Serial port master / slave (slave), Serial clock polarity (not inverted), DSP Mode disabled, DAC interface format (I2C)
    write_register(CS_REG_INTERFACE_CTL1, 0x04);

    // Set volume the master volume
    set_volume(volume);
    
    // Set speaker mono mode
    write_register(CS_REG_PLAYBACK_CTL2, 0x06);
    
    // Set speaker attenuation level
    write_register(CS_REG_SPEAKER_A_VOL, 0x00);
    write_register(CS_REG_SPEAKER_B_VOL, 0x00);
    
    // Disable analog soft ramp
    write_register(CS_REG_ANALOG_SR, 0x00);
    
    // Disable digital soft ramp
    write_register(CS_REG_MISC_CTL, 0x04);
    
    // Disable limiter attack level
    write_register(CS_REG_LIMIT_CTL1, 0x00);
    
    // Adjust bass and trebel levels
    write_register(CS_REG_TONE_CTL, 0x0F);
    
    // Adjust PCM volume level
    write_register(CS_REG_PCMA_VOL, 0x0A);
    write_register(CS_REG_PCMB_VOL, 0x0A);

    init_dma();
}

void CS43L22Dac::init_gpio() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // I2C
    RCC_AHB1PeriphClockCmd(RCC_GPIO_I2C_PERIPH, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    
    GPIO_PinAFConfig(GPIOx_I2C, GPIO_PS_I2C_SCL, GPIO_I2C_AFx);
    GPIO_PinAFConfig(GPIOx_I2C, GPIO_PS_I2C_SDA, GPIO_I2C_AFx);

    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_I2C_SCL | GPIO_PIN_I2C_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOx_I2C, &GPIO_InitStructure);

    // I2S
    RCC_AHB1PeriphClockCmd(RCC_GPIO_I2S_PERIPH, ENABLE);
    
    GPIO_StructInit(&GPIO_InitStructure);

    GPIO_PinAFConfig(GPIO2_I2S, GPIO_PS_I2S_MCK, GPIO_I2S_TX_AFx);
    GPIO_PinAFConfig(GPIO2_I2S, GPIO_PS_I2S_CK, GPIO_I2S_TX_AFx);
    GPIO_PinAFConfig(GPIO2_I2S, GPIO_PS_I2S_SD, GPIO_I2S_TX_AFx);
    GPIO_PinAFConfig(GPIO1_I2S, GPIO_PS_I2S_WS, GPIO_I2S_TX_AFx);

    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_I2S_MCK | GPIO_PIN_I2S_CK \
        | GPIO_PIN_I2S_SD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2_I2S, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_I2S_WS;
    GPIO_Init(GPIO1_I2S, &GPIO_InitStructure);
}

void CS43L22Dac::init_i2c() {
    I2C_InitTypeDef I2C_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_I2C_PERIPH, ENABLE);

    I2C_StructInit(&I2C_InitStructure);
    I2C_DeInit(I2Cx);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_InitStructure.I2C_OwnAddress1 = 0x36;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    
    I2C_Init(I2Cx, &I2C_InitStructure);
    I2C_Cmd(I2Cx, ENABLE);
}

void CS43L22Dac::init_i2s() {
    I2S_InitTypeDef i2s_init;

    RCC_APB1PeriphClockCmd(RCC_SPI_I2S_CLOCK, ENABLE);
    RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S);
    
    RCC_PLLI2SCmd(ENABLE);

    SPI_I2S_DeInit(SPI_I2S);
    i2s_init.I2S_AudioFreq = 44100;
    i2s_init.I2S_Standard = I2S_Standard_Phillips;
    i2s_init.I2S_DataFormat = I2S_DataFormat_16b;
    i2s_init.I2S_CPOL = I2S_CPOL_Low;
    i2s_init.I2S_Mode = I2S_Mode_MasterTx;
    i2s_init.I2S_MCLKOutput = I2S_MCLKOutput_Enable;

    I2S_Init(SPI_I2S, &i2s_init);
}

void CS43L22Dac::init_dma() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    DMA_DeInit(I2S_DMA_TX_STREAM);
    
    dma_tx_.DMA_Channel = I2S_DMA_TX_CHANNEL;
    dma_tx_.DMA_PeripheralBaseAddr = (uint32_t)(&(SPI_I2S->DR));
    dma_tx_.DMA_Memory0BaseAddr = (uint32_t)tx_dma_buf_;
    dma_tx_.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    dma_tx_.DMA_BufferSize = DAC_BUF_SIZE;
    dma_tx_.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_tx_.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_tx_.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    dma_tx_.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    dma_tx_.DMA_Mode = DMA_Mode_Circular;
    dma_tx_.DMA_Priority = DMA_Priority_High;
    dma_tx_.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma_tx_.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    dma_tx_.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma_tx_.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    
    DMA_Init(I2S_DMA_TX_STREAM, &dma_tx_);
    DMA_Cmd(I2S_DMA_TX_STREAM, ENABLE);

    DMA_ITConfig(I2S_DMA_TX_STREAM, DMA_IT_TC, ENABLE);
    NVIC_EnableIRQ(I2S_TX_DMA_IRQ);

    SPI_I2S_DMACmd(SPI_I2S, SPI_I2S_DMAReq_Tx, ENABLE);
}

// Adjust and set the volume, 0 - 255.
void CS43L22Dac::set_volume(uint8_t volume) {
    uint8_t converted_volume;
    
    // Master volume from the datasheet:
    // 0 = -102db
    // 230 = 0db
    // 24 = +12db
    if (volume > 230) {
        converted_volume = volume - 231;
    } else {
        converted_volume = volume + 25;
    }

    write_register(CS_REG_MASTER_A_VOL, converted_volume);
    write_register(CS_REG_MASTER_B_VOL, converted_volume);
}

void CS43L22Dac::FillTxBuffer() {
    fill_callback_((Frame *)tx_dma_buf_, DAC_FRAME_COUNT);
}

void CS43L22Dac::write_register(uint8_t reg, uint8_t value) {
    write_start();
    write_raw(reg);
    write_raw(value);
    write_stop();
}

void CS43L22Dac::write_start() {
    I2C_WAIT_FOR_FLAG(I2Cx, I2C_FLAG_BUSY);
    I2C_GenerateSTART(I2Cx, ENABLE);
    I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_MODE_SELECT);
    I2C_Send7bitAddress(I2Cx, DEFAULT_DEVICE_ADDRESS, I2C_Direction_Transmitter);
    I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
}

void CS43L22Dac::write_stop() {
    I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
    I2C_GenerateSTOP(I2Cx, ENABLE);
}

void CS43L22Dac::write_raw(uint16_t* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        I2C_SendData(I2Cx, data[i] & 0xFF);
        I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
        I2C_SendData(I2Cx, data[i] >> 8);
        I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
    }
}

void CS43L22Dac::write_raw(uint8_t data) {
    write_raw(&data, 1);
}

void CS43L22Dac::write_raw(uint8_t* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        I2C_SendData(I2Cx, data[i]);
        I2C_WAIT_FOR_EVENT(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
    }
}

extern "C" {
void DMA1_Stream7_IRQHandler(void) {
    if (DMA_GetFlagStatus(I2S_DMA_TX_STREAM, I2S_DMA_TX_TC_FLAG) != RESET) {
        DMA_ClearFlag(I2S_DMA_TX_STREAM, I2S_DMA_TX_TC_FLAG);
        
        CS43L22Dac::GetGlobalInstance()->FillTxBuffer();
    }
}
}
