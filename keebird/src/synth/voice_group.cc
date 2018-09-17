#include "voice_group.h"

#include <cstdio>

namespace synth {

VoiceGroup::VoiceGroup(const uint32_t sample_rate,
                       const uint32_t control_rate)
    : current_voice_index_(0),
      voices_({
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
            { sample_rate, control_rate },
        })
{ }

void VoiceGroup::Trigger(const Note* note) {
    Voice* next_voice = &voices_[current_voice_index_];
    next_voice->Trigger(note);
    current_voice_index_ = (current_voice_index_ + 1) % N_VOICES;
}

void VoiceGroup::TickControl() {
    Voice* voice;

    for (unsigned int i = 0; i < N_VOICES; i++) {
        voice = &voices_[i];
        voice->TickControl();
    }
}

void VoiceGroup::TickAudio() {
    Voice* voice;
    
    for (unsigned int i = 0; i < N_VOICES; i++) {
        voice = &voices_[i];
        voice->TickAudio();
    }
}

int16_t VoiceGroup::Value() {
    int16_t samples[N_VOICES];
    int32_t sample = 0;
    uint8_t active_voices = 0;
    Voice* voice;

    for (unsigned int i = 0; i < N_VOICES; i++) {
        voice = &voices_[i];
        samples[i] = voice->Value();
        if (samples[i] > 0) {
            active_voices++;
        }
    }

    if (active_voices == 0) {
        return 0;
    }

    for (unsigned int i = 0; i < N_VOICES; i++) {
        if (samples[i] > 0) {
            sample = sample + (samples[i] / active_voices);
        }
    }

    return (int16_t)sample;
}

}
