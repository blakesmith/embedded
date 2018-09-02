#ifndef KEEBIRD_AUDIO_PIPELINE_H_
#define KEEBIRD_AUDIO_PIPELINE_H_

#include "osc.h"
#include "adsr_envelope.h"
#include "mixer.h"

#include <cstddef>

namespace keebird {

static constexpr size_t N_OSC = 2;

class AudioPipeline {
public:
    AudioPipeline(const uint32_t sample_rate,
                  const uint32_t control_rate);
    ~AudioPipeline() = default;

    void Fill(int16_t* buffer, size_t frames, uint8_t channel_count);
    
private:
    const uint32_t sample_rate_;
    const uint32_t control_rate_;

    uint32_t samples_per_control_;
    uint32_t phase_;

    Osc osc_[N_OSC];
    AdsrEnvelope envelope_;
    Mixer<N_OSC> mixer_;
};

}

#endif
