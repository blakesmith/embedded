#include "adsr_envelope.h"

namespace keebird {

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
      sustain_level_(sustain_level) {
          compute_segment_positions();
          Reset();
      }

uint32_t AdsrEnvelope::get_last_segment_position() {
    if (segment_ == ENVELOPE_SEGMENT_ATTACK) {
        return 0;
    } else {
        return segment_positions_[segment_-1];
    }
}

void AdsrEnvelope::compute_segment_positions(uint32_t* current,
                                             uint32_t* last) {
    uint32_t current_segment_position = segment_positions_[segment_];
    uint32_t last_segment_position = get_last_segment_position();
    
    while (phase_ >= current_segment_position && segment_ != ENVELOPE_SEGMENT_RELEASE) {
        segment_++;
        current_segment_position = segment_positions_[segment_];
        last_segment_position = get_last_segment_position();
    }

    if (current != NULL) {
        *current = current_segment_position;
    }
    if (last != NULL) {
        *last = last_segment_position;
    }
}

uint8_t AdsrEnvelope::interpolate_segment(uint8_t start,
                                          uint8_t end,
                                          uint32_t segment_phase,
                                          uint32_t total_segment_duration) {
    if (start > end) {
        return start - ((segment_phase << 8) / total_segment_duration * (start - end) >> 8);
    } else {
        return (segment_phase << 8) / total_segment_duration * (end - start) >> 8;
    }
}

uint8_t AdsrEnvelope::compute_next_value(uint32_t current_segment_position,
                                         uint32_t last_segment_position) {
    uint32_t total_segment_duration = current_segment_position - last_segment_position;
    uint32_t segment_phase = phase_ - last_segment_position;

    if (segment_ == ENVELOPE_SEGMENT_ATTACK) {
        // Step from 0 to 255
        return interpolate_segment(0, 255, segment_phase, total_segment_duration);
    } else if (segment_ == ENVELOPE_SEGMENT_DECAY) {
        // Step from 255 to sustain_value_
        return interpolate_segment(255, sustain_level_, segment_phase, total_segment_duration);
    } else if (segment_ == ENVELOPE_SEGMENT_SUSTAIN) {
        // Hold the sustain value
        return value_;
    } else if (segment_ == ENVELOPE_SEGMENT_RELEASE) {
        // Step from sustain_value_ to 0
        return interpolate_segment(sustain_level_, 0, segment_phase, total_segment_duration);
    } else {
        // Should never get here!
        return 0;
    }
}

void AdsrEnvelope::Tick() {
    phase_++;
    
    uint32_t current_segment_position;
    uint32_t last_segment_position;

    compute_segment_positions(&current_segment_position, &last_segment_position);
    value_ = compute_next_value(current_segment_position, last_segment_position);
}

int16_t AdsrEnvelope::Apply(int16_t in_val) {
    return (static_cast<int32_t>(in_val) * value_) >> 8;
}

void AdsrEnvelope::Reset() {
    phase_ = 0;
    segment_ = ENVELOPE_SEGMENT_ATTACK;

    uint32_t current_segment_position;
    uint32_t last_segment_position;

    compute_segment_positions(&current_segment_position, &last_segment_position);
    value_ = compute_next_value(current_segment_position, last_segment_position);
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
