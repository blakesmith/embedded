#ifndef NOME_SETTINGS_H_
#define NOME_SETTINGS_H_

#include <cstddef>

namespace nome {

class Settings {
public:
    Settings();
    ~Settings() = default;

    uint16_t AddAndGetBPM(int8_t bpm);
    
    const uint32_t sample_rate;
    const uint32_t control_rate;
    const uint8_t channel_count;
    const size_t frames_per_period;
    
    uint16_t current_bpm;
    uint16_t current_downbeat;
};

}

#endif
