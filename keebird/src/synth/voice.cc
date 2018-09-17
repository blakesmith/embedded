#include "voice.h"

namespace synth {

static const uint16_t STARTING_FREQ = 0;

Voice::Voice(const uint32_t sample_rate,
             const uint32_t control_rate)
    : osc_({
              {OscShape::SQUARE, sample_rate, STARTING_FREQ},
              {OscShape::SIN, sample_rate, STARTING_FREQ}
          }),
    envelope_(control_rate, 2550, 1, 20, 0, 225, 0) {
    uint8_t levels[N_OSC] = {127, 127};
    mixer_.set_levels(levels, N_OSC);
    envelope_.Reset();
}

void Voice::Trigger(const Note* note) {
    for (size_t j = 0; j < N_OSC; j++) {
        osc_[j].set_freq(note->frequency);
    }
    envelope_.Reset();
}

void Voice::TickAudio() {
    for (size_t i = 0; i < N_OSC; i++) {
        osc_[i].Tick();
    }
}

void Voice::TickControl() {
    envelope_.Tick();
}

int16_t Voice::Value() {
    for (size_t i = 0; i < N_OSC; i++) {
        mixer_.set_input(envelope_.Apply(osc_[i].Value()), i);
    }
    return mixer_.Value();
}

}
