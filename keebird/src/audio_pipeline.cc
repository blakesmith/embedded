#include "audio_pipeline.h"

namespace keebird {

static const uint16_t STARTING_FREQ = 0;

AudioPipeline::AudioPipeline(const uint32_t sample_rate,
                             const uint32_t control_rate)
    : sample_rate_(sample_rate),
      control_rate_(control_rate),
      samples_per_control_(sample_rate_ / control_rate_),
      phase_(0),
      voices_(sample_rate, control_rate)
{ }

void AudioPipeline::Fill(int16_t* buffer, size_t frames, uint8_t channel_count) {
    for (size_t i = 0; i < frames; i++) {
        voices_.TickAudio();
        int16_t sample = voices_.Value();

        for (size_t j = 0; j < channel_count; j++) {
            buffer[i*channel_count+j] = sample;
        }
        
        phase_++;

        if (phase_ % samples_per_control_ == 0) {
            voices_.TickControl();
        }
    }
}

void AudioPipeline::Trigger(const Note* note) {
    voices_.Trigger(note);
}

}
