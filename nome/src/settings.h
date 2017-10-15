#ifndef NOME_SETTINGS_H_
#define NOME_SETTINGS_H_

#include <cstddef>

namespace nome {

class Settings {
public:
    Settings();
    ~Settings() = default;

    void AddBPM(int16_t bpm);
    void AddDownbeat(int8_t downbeat);
    void AddVolume(int8_t volume);

    uint32_t GetSampleRate() const;
    uint32_t GetControlRate() const;
    uint8_t GetChannelCount() const;
    uint16_t GetBPM() const;
    uint8_t GetDownbeat() const;
    uint8_t GetVolume() const;
    
private:
    const uint32_t sample_rate_;
    const uint32_t control_rate_;
    const uint8_t channel_count_;

    uint16_t current_bpm_;
    uint8_t current_downbeat_;
    uint8_t current_volume_;
};

}

#endif
