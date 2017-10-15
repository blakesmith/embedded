#include "settings.h"

namespace nome {

static constexpr uint8_t MAX_VOLUME = 0x0F;
static constexpr uint8_t MAX_DOWNBEAT = 0x0F;
static constexpr uint16_t MAX_BPM = 0x200;

Settings::Settings()
    : sample_rate_(44100),
      control_rate_(sample_rate_ / 10),
      channel_count_(2),
      current_bpm_(120),
      current_downbeat_(4),
      current_volume_(11) { }

void Settings::AddBPM(int16_t bpm) {
    int16_t value = (int16_t)current_bpm_ + bpm;
    if (value < 0) {
        value = 0;
    } else if (value > MAX_BPM) {
        value = MAX_BPM;
    }
    current_bpm_ = (uint16_t)value;
}

void Settings::AddDownbeat(int8_t downbeat) {
    int8_t value = (int8_t)current_downbeat_ + downbeat;
    if (value < 0) {
        value = 0;
    } else if (value > MAX_DOWNBEAT) {
        value = MAX_DOWNBEAT;
    }
    current_downbeat_ = (uint8_t)value;
}

void Settings::AddVolume(int8_t volume) {
    int8_t value = (int8_t)current_volume_ + volume;
    if (value < 0) {
        value = 0;
    } else if (value > MAX_VOLUME) {
        value = MAX_VOLUME;
    }
    current_volume_ = (uint8_t)value;
}

uint32_t Settings::GetSampleRate() const {
    return sample_rate_;
}

uint32_t Settings::GetControlRate() const {
    return control_rate_;
}

uint8_t Settings::GetChannelCount() const {
    return channel_count_;
}

uint16_t Settings::GetBPM() const {
    return current_bpm_;
}

uint8_t Settings::GetDownbeat() const {
    return current_downbeat_;
}

uint8_t Settings::GetVolume() const {
    return current_volume_;
}

}
