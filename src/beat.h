#ifndef NOME_BEAT_H_
#define NOME_BEAT_H_

#include "osc.h"
#include "adsr_envelope.h"

#include <cstddef>

namespace nome {
class Beat {
public:
    Beat(const uint32_t sample_rate,
         const uint32_t control_rate);

    ~Beat() = default;

    void Fill(int16_t* buffer, size_t frames, uint8_t channel_count);

private:
    const uint32_t sample_rate_;
    const uint32_t control_rate_;
    
    uint32_t phase_;
    Osc osc_;
    AdsrEnvelope envelope_;
};

}

#endif
