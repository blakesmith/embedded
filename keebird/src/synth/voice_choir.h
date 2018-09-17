#ifndef SYNTH_VOICE_CHOIR_H_
#define SYNTH_VOICE_CHOIR_H_

#include <cstdint>
#include <cstddef>

#include "voice.h"

namespace synth {

static constexpr size_t N_VOICES = 12;

class VoiceChoir {
public:
    VoiceChoir(const uint32_t sample_rate,
               const uint32_t control_rate);
    ~VoiceChoir() = default;

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
