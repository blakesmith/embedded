#ifndef SYNTH_VOICE_CHOIR_H_
#define SYNTH_VOICE_CHOIR_H_

#include <cstdint>
#include <cstddef>

#include "voice.h"

namespace synth {

static constexpr size_t N_VOICES = 12;

class VoiceGroup {
public:
    VoiceGroup(const uint32_t sample_rate,
               const uint32_t control_rate);
    ~VoiceGroup() = default;

    void Trigger(const Note* note);
    void TickControl();
    void TickAudio();

    int16_t Value();

private:
    uint8_t current_voice_index_;
    Voice voices_[N_VOICES];
};

}

#endif
