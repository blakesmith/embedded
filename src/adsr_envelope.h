#ifndef NOME_ADSR_ENVELOPE_H_
#define NOME_ADSR_ENVELOPE_H_

#include <cstddef>
#include <cstdint>

namespace nome {

class AdsrEnvelope {
public:
    AdsrEnvelope(const uint32_t control_rate,
                 const uint32_t total_duration_ms,
                 const uint8_t attack,
                 const uint8_t decay,
                 const uint8_t sustain,
                 const uint8_t release);

    ~AdsrEnvelope() = default;

    void Tick();
    uint8_t Value();

    void compute_segment_positions();

private:
    const uint32_t control_rate_;
    const uint32_t total_duration_ms_;
    const uint32_t segment_values_[4];

    uint32_t phase_;
    size_t segment_;
    uint32_t segment_positions_[4];
};
    
}

#endif
