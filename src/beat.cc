#include "beat.h"

namespace nome {

Beat::Beat(const uint32_t sample_rate,
           const uint32_t control_rate)
    : sample_rate_(sample_rate),
      control_rate_(control_rate),
      phase_(0),
      osc_(OscShape::OSC_SHAPE_SIN, sample_rate, 172, 50),
      envelope_(1, 10, 0, 244) { }

void Beat::Fill(int16_t* buffer, size_t frames, uint8_t channel_count) {
    const uint32_t samples_per_control = sample_rate_ / control_rate_;
    
    for (size_t i = 0; i < frames; i++) {
        osc_.Tick();
        phase_++;
        if (phase_ % samples_per_control) {
            envelope_.Tick();
        }

        for (size_t j = 0; j < channel_count; j++) {
            buffer[i+j] = static_cast<int16_t>(osc_.Value() * envelope_.Value());
        }
    }
}

}
