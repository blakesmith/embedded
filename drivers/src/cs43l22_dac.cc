#include "cs43l22_dac.h"

#include "stm32f4xx_gpio.h"
#include "i2c_common.h"

void CS43L22Dac::Init(uint8_t volume) {
    init_i2c();

    // TODO: Init I2S?
    
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
}

void CS43L22Dac::init_i2c() {
    // TODO: Implement
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

void CS43L22Dac::write_register(uint8_t reg, uint8_t value) {
}

