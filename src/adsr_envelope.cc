#include "adsr_envelope.h"

namespace nome {

AdsrEnvelope::AdsrEnvelope(const uint32_t control_rate,
                           const uint16_t total_duration_fixed_ms,
                           const uint8_t attack,
                           const uint8_t decay,
                           const uint8_t sustain,
                           const uint8_t release,
                           const uint8_t sustain_level)
    : control_rate_(control_rate),
      total_duration_fixed_ms_(total_duration_fixed_ms),
      segment_values_{ attack, decay, sustain, release },
      sustain_level_(sustain_level),
      value_(0xFF),
      phase_(0),
      segment_(ENVELOPE_SEGMENT_ATTACK) {
          compute_segment_positions();
      }

uint32_t AdsrEnvelope::get_last_segment_position() {
    if (segment_ == ENVELOPE_SEGMENT_ATTACK) {
        return 0;
    } else {
        return segment_positions_[segment_-1];
    }
}

void AdsrEnvelope::Tick() {
    phase_++;
    uint32_t current_segment_position = segment_positions_[segment_];
    uint32_t last_segment_position = get_last_segment_position();
    
    while (phase_ >= current_segment_position && segment_ != ENVELOPE_SEGMENT_RELEASE) {
        segment_++;
        current_segment_position = segment_positions_[segment_];
        last_segment_position = get_last_segment_position();
    }

    uint32_t total_segment_duration = current_segment_position - last_segment_position;
    uint32_t segment_phase = phase_ - last_segment_position;

    if (segment_ == ENVELOPE_SEGMENT_ATTACK) {
        // Step from 0 to 255
        value_ = (segment_phase << 8) / total_segment_duration * 0xFF >> 8;
    } else if (segment_ == ENVELOPE_SEGMENT_DECAY) {
        // Step from 255 to sustain_value_
        value_ = 0xFF - ((segment_phase << 8) / total_segment_duration * (0xFF - sustain_level_) >> 8);
    } else if (segment_ == ENVELOPE_SEGMENT_SUSTAIN) {
        // Hold the sustain value
    } else if (segment_ == ENVELOPE_SEGMENT_RELEASE) {
        // Step from sustain_value_ to 0
        value_ = sustain_level_ - ((segment_phase << 8) / total_segment_duration * sustain_level_ >> 8);
    }
}

void AdsrEnvelope::Hit() {
    // phase_ = 0;
    // segment_ = ENVELOPE_SEGMENT_ATTACK;
    // uint32_t segment_position = advance_segment();
    // calculate_next_value();
}

uint8_t AdsrEnvelope::Value() {
    return value_;
}

void AdsrEnvelope::compute_segment_positions() {
    for (size_t i = 0; i < 4; i++) {
        uint8_t segment_value = segment_values_[i];
        uint32_t total_duration = (control_rate_ * total_duration_fixed_ms_) >> 8;
        segment_positions_[i] = (total_duration * segment_value) >> 8;
    }
}

}
