#include "beat.h"

namespace nome {

Beat::Beat(const uint32_t sample_rate,
           const uint32_t control_rate,
           const uint16_t bpm)
    : sample_rate_(sample_rate),
      control_rate_(control_rate),
      bpm_(bpm),
      samples_per_beat_((sample_rate * 60) / bpm),
      samples_per_control_(sample_rate_ / control_rate_),
      phase_(0),
      osc_(OscShape::OSC_SHAPE_SIN, sample_rate, 1320, 50),
      envelope_(control_rate, 255, 1, 10, 0, 244, 0) { }

void Beat::Fill(int16_t* buffer, size_t frames, uint8_t channel_count) {
    for (size_t i = 0; i < frames; i++) {
        for (size_t j = 0; j < channel_count; j++) {
            int16_t sample = (static_cast<int32_t>(osc_.Value()) * envelope_.Value()) >> 8;
            buffer[i*channel_count+j] = sample;
        }

        osc_.Tick();
        phase_++;
        if (phase_ % samples_per_beat_ == 0) {
            envelope_.Reset();
        }
        if (phase_ % samples_per_control_ == 0) {
            envelope_.Tick();
        }
    }
}

}
