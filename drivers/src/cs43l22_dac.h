#ifndef CS43L22_DAC_H_
#define CS43L22_DAC_H_

#include <stm32f4xx_dma.h>
#include <cstddef>

static constexpr uint8_t DEFAULT_DEVICE_ADDRESS = 0x25 << 1;

static constexpr uint8_t CS_REG_ID = 0x01;
static constexpr uint8_t CS_REG_POW_CTL1 = 0x02;
static constexpr uint8_t CS_REG_POW_CTL2 = 0x04;
static constexpr uint8_t CS_REG_CLOCKING_CTL = 0x05;
static constexpr uint8_t CS_REG_INTERFACE_CTL1 = 0x06;
static constexpr uint8_t CS_REG_ANALOG_SR = 0x0A;
static constexpr uint8_t CS_REG_MISC_CTL = 0x0E;
static constexpr uint8_t CS_REG_PLAYBACK_CTL2 = 0x0F;
static constexpr uint8_t CS_REG_PCMA_VOL = 0x1A;
static constexpr uint8_t CS_REG_PCMB_VOL = 0x1B;
static constexpr uint8_t CS_REG_TONE_CTL = 0x1F;
static constexpr uint8_t CS_REG_MASTER_A_VOL = 0x20;
static constexpr uint8_t CS_REG_MASTER_B_VOL = 0x21;
static constexpr uint8_t CS_REG_SPEAKER_A_VOL = 0x24;
static constexpr uint8_t CS_REG_SPEAKER_B_VOL = 0x25;
static constexpr uint8_t CS_REG_LIMIT_CTL1 = 0x27;

static constexpr uint8_t CS_OUT_AUTO = 0x05;
static constexpr uint8_t CS_CLOCKING_AUTO = 0x81;

static constexpr uint32_t DAC_FRAME_COUNT = 32;
static constexpr uint32_t DAC_BUF_SIZE = DAC_FRAME_COUNT * 2;

class CS43L22Dac {
public:
    CS43L22Dac() = default;
    ~CS43L22Dac() = default;

    struct Frame {
        int16_t left;
        int16_t right;
    };

    typedef void (*DacFillCallback)(Frame *tx, size_t size);
    
    void Init(uint8_t volume,
              uint32_t sample_rate,
              DacFillCallback fill_callback);

    void FillTxBuffer();
    
    static CS43L22Dac *GetGlobalInstance() {
        return global_dac_;
    };
    
private:
    void init_gpio();
    void init_i2c();
    void init_i2s();
    void init_dma();
    void write_register(uint8_t reg, uint8_t value);
    void set_volume(uint8_t volume);

    void write_start();
    void write_stop();
    void write_raw(uint8_t* data, size_t size);
    void write_raw(uint16_t* data, size_t size);
    void write_raw(uint8_t data);

    uint32_t sample_rate_;
    DacFillCallback fill_callback_;
    DMA_InitTypeDef dma_tx_;

    int16_t tx_dma_buf_[DAC_BUF_SIZE];

    static CS43L22Dac* global_dac_;
};

#endif
