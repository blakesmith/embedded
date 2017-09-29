#ifndef CS43L22_DAC_H_
#define CS43L22_DAC_H_

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

class CS43L22Dac {
public:
    CS43L22Dac() = default;
    ~CS43L22Dac() = default;
    
    void Init(uint8_t volume);
private:
    void init_i2c();
    void init_i2s();
    void write_register(uint8_t reg, uint8_t value);
    void set_volume(uint8_t volume);
};

#endif
