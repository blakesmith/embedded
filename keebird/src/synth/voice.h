#ifndef SYNTH_VOICE_H_
#define SYNTH_VOICE_H_

#include <cstdint>
#include <cstddef>

#include "adsr_envelope.h"
#include "mixer.h"
#include "note.h"
#include "osc.h"

namespace synth {

static constexpr size_t N_OSC = 2;

class Voice {
public:
    Voice(const uint32_t sample_rate,
          const uint32_t control_rate);
    ~Voice() = default;

    void Trigger(const Note* note);
    void TickControl();
    void TickAudio();

    int16_t Value();

private:
    Osc osc_[N_OSC];
    AdsrEnvelope envelope_;
    Mixer<N_OSC> mixer_;
};

}

#endif
