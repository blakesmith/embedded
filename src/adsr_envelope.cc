#include "adsr_envelope.h"

namespace nome {

AdsrEnvelope::AdsrEnvelope(const uint32_t control_rate,
                           const uint32_t total_duration_ms,
                           const uint8_t attack,
                           const uint8_t decay,
                           const uint8_t sustain,
                           const uint8_t release)
    : control_rate_(control_rate),
      total_duration_ms_(total_duration_ms),
      segment_values_{ attack, decay, sustain, release },
      phase_(0),
      segment_(0) {
          compute_segment_positions();
      }

void AdsrEnvelope::Tick() {
    phase_++;
}

uint8_t AdsrEnvelope::Value() {
    return 0xFF;
}

void AdsrEnvelope::compute_segment_positions() {
    for (size_t i = 0; i < 4; i++) {
        uint32_t segment_value = segment_values_[i];
    }
}

}
