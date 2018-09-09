#include "audio_pipeline.h"

namespace keebird {

static const uint16_t STARTING_FREQ = 0;

AudioPipeline::AudioPipeline(const uint32_t sample_rate,
                             const uint32_t control_rate)
    : sample_rate_(sample_rate),
      control_rate_(control_rate),
      samples_per_control_(sample_rate_ / control_rate_),
      phase_(0),
      osc_({
              {OscShape::SQUARE, sample_rate, STARTING_FREQ},
              {OscShape::SIN, sample_rate, STARTING_FREQ}
          }),
    envelope_(control_rate, 2550, 1, 20, 0, 225, 0) {
    uint8_t levels[N_OSC] = {200, 30};
    mixer_.set_levels(levels, N_OSC);
    envelope_.Reset();
}

void AudioPipeline::Fill(int16_t* buffer, size_t frames, uint8_t channel_count) {
    for (size_t i = 0; i < frames; i++) {
        for (size_t j = 0; j < N_OSC; j++) {
            mixer_.set_input(envelope_.Apply(osc_[j].Value()), j);
            osc_[j].Tick();
        }
        int16_t sample = mixer_.Value();

        for (size_t j = 0; j < channel_count; j++) {
            buffer[i*channel_count+j] = sample;
        }
        
        phase_++;

        if (phase_ % samples_per_control_ == 0) {
            envelope_.Tick();
        }
    }
}

void AudioPipeline::Trigger() {
    envelope_.Reset();
}

void AudioPipeline::Trigger(const Note* note) {
    for (size_t j = 0; j < N_OSC; j++) {
        osc_[j].set_freq(note->frequency);
    }
    envelope_.Reset();
}

}
