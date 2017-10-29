#include "cs43l22_dac.h"

#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "misc.h"

#include <cstring>

#define DELAY(t) {                 \
  uint32_t timeout = t; \
  while (true) { if ((timeout--) == 0) break; } \
}

// Static instance, for the IRQ handler
CS43L22Dac *CS43L22Dac::global_dac_;

static constexpr uint32_t DEFAULT_TIMEOUT = 0x1000 * 300;

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

CS43L22Dac::CS43L22Dac(I2CBus& i2c_bus,
                       GPIOPin& reset_pin)
    : i2c_bus_(i2c_bus),
      reset_pin_(reset_pin)
{}

void CS43L22Dac::Init(uint8_t volume,
                      uint32_t sample_rate,
                      DacFillCallback fill_callback) {
    global_dac_ = this;
    sample_rate_ = sample_rate;
    fill_callback_ = fill_callback;
    current_buffer_ = tx_dma_buf0_;

    memset(tx_dma_buf0_, 0, DAC_BUF_SIZE);
    memset(tx_dma_buf1_, 0, DAC_BUF_SIZE);

    init_gpio();
    reset();
    init_i2s();
    init_codec(volume);
    init_dma();
}

void CS43L22Dac::Start() {
    FillTxBuffer();
    I2S_Cmd(SPI_I2S, ENABLE);
    DMA_Cmd(I2S_DMA_TX_STREAM, ENABLE);
}

void CS43L22Dac::reset() {
    reset_pin_.set_mode(GPIOPin::Mode::OUT);
    reset_pin_.set_speed(GPIOPin::Speed::TWO_MHZ);
    reset_pin_.set_output(GPIOPin::OType::PUSH_PULL);
    reset_pin_.set_pupd(GPIOPin::PuPd::DOWN);
    reset_pin_.Init();

    reset_pin_.Set(true);
    DELAY(DEFAULT_TIMEOUT);
    reset_pin_.Set(false);
    DELAY(DEFAULT_TIMEOUT);
}

void CS43L22Dac::init_gpio() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // I2S
    RCC_AHB1PeriphClockCmd(RCC_GPIO_I2S_PERIPH, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_I2S_MCK | GPIO_PIN_I2S_CK \
        | GPIO_PIN_I2S_SD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIO2_I2S, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_I2S_WS;
    GPIO_Init(GPIO1_I2S, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIO2_I2S, GPIO_PS_I2S_MCK, GPIO_I2S_TX_AFx);
    GPIO_PinAFConfig(GPIO2_I2S, GPIO_PS_I2S_CK, GPIO_I2S_TX_AFx);
    GPIO_PinAFConfig(GPIO2_I2S, GPIO_PS_I2S_SD, GPIO_I2S_TX_AFx);
    GPIO_PinAFConfig(GPIO1_I2S, GPIO_PS_I2S_WS, GPIO_I2S_TX_AFx);
}

void CS43L22Dac::init_i2s() {
    I2S_InitTypeDef i2s_init;

    RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S);
    RCC_PLLI2SCmd(ENABLE);

    while (RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY) == RESET);

    RCC_APB1PeriphClockCmd(RCC_SPI_I2S_CLOCK, ENABLE);
    
    SPI_I2S_DeInit(SPI_I2S);
    i2s_init.I2S_AudioFreq = sample_rate_;
    i2s_init.I2S_Standard = I2S_Standard_Phillips;
    i2s_init.I2S_DataFormat = I2S_DataFormat_16b;
    i2s_init.I2S_CPOL = I2S_CPOL_Low;
    i2s_init.I2S_Mode = I2S_Mode_MasterTx;
    i2s_init.I2S_MCLKOutput = I2S_MCLKOutput_Enable;

    I2S_Init(SPI_I2S, &i2s_init);
}

void CS43L22Dac::init_codec(uint8_t volume) {
    uint8_t reg;
    
    // Hold power off
    write_register(CS_REG_POW_CTL1, 0x01);

    // Start initialization sequence, p. 32

    write_register(0x00, 0x99);
    write_register(0x47, 0x80);
    reg = read_register(0x32);
    write_register(0x32, reg | 0x80);
    reg = read_register(0x32);
    write_register(0x32, reg & (~0x80));
    write_register(0x00, 0x00);

    // End initialization sequence
    
    // Set the output device to auto detect, headphone or speaker depending on if the headphones are plugged in
    write_register(CS_REG_POW_CTL2, CS_OUT_AUTO);

    // Configure the clocking control to AUTO, and enable MCLKDIV2
    write_register(CS_REG_CLOCKING_CTL, CS_CLOCKING_AUTO);

    // Serial port master / slave (slave), Serial clock polarity (not inverted), DSP Mode disabled, DAC interface format (I2S)
    write_register(CS_REG_INTERFACE_CTL1, 0x07);

    // Set volume the master volume
    SetVolume(volume);
    
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

    // Power up the device
    write_register(CS_REG_POW_CTL1, 0x9E);
}

void CS43L22Dac::init_dma() {
    DMA_InitTypeDef dma_init;
    NVIC_InitTypeDef nvic_init;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

    DMA_Cmd(I2S_DMA_TX_STREAM, DISABLE);
    DMA_DeInit(I2S_DMA_TX_STREAM);

    DMA_StructInit(&dma_init);
    dma_init.DMA_Channel = I2S_DMA_TX_CHANNEL;
    dma_init.DMA_PeripheralBaseAddr = (uint32_t)(&(SPI_I2S->DR));
    dma_init.DMA_Memory0BaseAddr = (uint32_t)tx_dma_buf0_;
    dma_init.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    dma_init.DMA_BufferSize = DAC_BUF_SIZE;
    dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    dma_init.DMA_Mode = DMA_Mode_Circular;
    dma_init.DMA_Priority = DMA_Priority_High;
    dma_init.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma_init.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    dma_init.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma_init.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(I2S_DMA_TX_STREAM, &dma_init);

    DMA_DoubleBufferModeConfig(I2S_DMA_TX_STREAM, (uint32_t)tx_dma_buf1_, DMA_Memory_1);
    DMA_DoubleBufferModeCmd(I2S_DMA_TX_STREAM, ENABLE);
    DMA_ITConfig(I2S_DMA_TX_STREAM, DMA_IT_TC | DMA_IT_TE, ENABLE);

    nvic_init.NVIC_IRQChannel = I2S_TX_DMA_IRQ;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);

    SPI_I2S_DMACmd(SPI_I2S, SPI_I2S_DMAReq_Tx, ENABLE);
}

// Adjust and set the volume, 0 - 255.
void CS43L22Dac::SetVolume(uint8_t volume) {
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
    fill_callback_((Frame *)current_buffer_, DAC_FRAME_COUNT, DAC_BUF_SIZE);
    if (current_buffer_ == tx_dma_buf0_) {
        current_buffer_ = tx_dma_buf1_;
    } else {
        current_buffer_ = tx_dma_buf0_;
    }
}

void CS43L22Dac::write_register(uint8_t reg, uint8_t value) {
    i2c_bus_.WriteTransmitStart(DEFAULT_DEVICE_ADDRESS);
    i2c_bus_.WriteRaw(reg);
    i2c_bus_.WriteRaw(value);
    i2c_bus_.WriteTransmitStop();
}

uint8_t CS43L22Dac::read_register(uint8_t reg) {
    uint8_t value;

    i2c_bus_.WriteTransmitStart(DEFAULT_DEVICE_ADDRESS);
    i2c_bus_.WriteRaw(reg);
    i2c_bus_.WriteTransmitStop();
    i2c_bus_.WriteReceiveStart(DEFAULT_DEVICE_ADDRESS);
    value = i2c_bus_.ReceiveData();
    i2c_bus_.WriteReceiveStop();
    return value;
}

extern "C" {
void DMA1_Stream7_IRQHandler(void) {
    if (DMA_GetFlagStatus(I2S_DMA_TX_STREAM, I2S_DMA_TX_TC_FLAG) != RESET) {
        DMA_ClearFlag(I2S_DMA_TX_STREAM, I2S_DMA_TX_TC_FLAG);
        
        CS43L22Dac::GetGlobalInstance()->FillTxBuffer();
    }
}
}
