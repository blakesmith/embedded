#ifndef NOME_ADSR_ENVELOPE_H_
#define NOME_ADSR_ENVELOPE_H_

#include <cstddef>
#include <cstdint>

namespace nome {

enum EnvelopeSegment {
    ENVELOPE_SEGMENT_ATTACK = 0,
    ENVELOPE_SEGMENT_DECAY = 1,
    ENVELOPE_SEGMENT_SUSTAIN = 2,
    ENVELOPE_SEGMENT_RELEASE = 3
};

class AdsrEnvelope {
public:
    AdsrEnvelope(const uint32_t control_rate,
                 const uint16_t total_duration_fixed_ms,
                 const uint8_t attack,
                 const uint8_t decay,
                 const uint8_t sustain,
                 const uint8_t sustain_level,
                 const uint8_t release);

    ~AdsrEnvelope() = default;

    void Tick();
    uint8_t Value();
    void Reset();

private:
    // Usually sample rate / 10. AKA - 44100 / 10 = 4410
    const uint32_t control_rate_;
    // 255 represents 1 second. Maximum 255 seconds (256 * 256)
    const uint16_t total_duration_fixed_ms_;
    // The value of each of the different segments.
    const uint8_t segment_values_[4];
    const uint8_t sustain_level_;

    uint8_t value_;
    uint32_t phase_;
    size_t segment_;
    uint32_t segment_positions_[4];

    uint8_t interpolate_segment(uint8_t start,
                                uint8_t end,
                                uint32_t segment_phase,
                                uint32_t total_segment_duration);
    void compute_segment_positions();
    void compute_segment_positions(uint32_t* current, uint32_t* last);
    uint8_t compute_next_value(uint32_t current_segment_position, uint32_t last_segment_position);
    uint32_t get_last_segment_position();
};
    
}

#endif
