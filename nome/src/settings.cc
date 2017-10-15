#include "settings.h"

namespace nome {

Settings::Settings()
    : sample_rate_(44100),
      control_rate_(sample_rate_ / 10),
      channel_count_(2),
      current_bpm_(120),
      current_downbeat_(4),
      current_volume_(128) { }

void Settings::AddBPM(int16_t bpm) {
    current_bpm_ += bpm;
}

void Settings::AddDownbeat(int8_t downbeat) {
    current_downbeat_ += downbeat;
}

void Settings::AddVolume(int8_t volume) {
    current_volume_ += volume;
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
