#include "beat.h"

#include <cstdint>

namespace nome {

static const uint16_t DOWNBEAT_FREQ = 1320;
static const uint16_t UPBEAT_FREQ = 880;

Beat::Beat(const uint32_t sample_rate,
           const uint32_t control_rate,
           const uint16_t bpm,
           const uint8_t downbeat)
    : sample_rate_(sample_rate),
      control_rate_(control_rate),
      bpm_(bpm),
      downbeat_(downbeat),
      samples_per_beat_((sample_rate * 60) / bpm),
      samples_per_control_(sample_rate_ / control_rate_),
      total_beats_(0),
      phase_(0),
      osc_({
              {OscShape::TRIANGLE, sample_rate, DOWNBEAT_FREQ},
              {OscShape::SIN, sample_rate, DOWNBEAT_FREQ}
          }),
      envelope_(control_rate, 255, 1, 20, 0, 225, 0),
      mixer_(osc_, BEAT_N_OSC),
      monitor_(&total_beats_) {
    SetDownbeat(downbeat_);
    uint8_t levels[BEAT_N_OSC] = {200, 55};
    mixer_.SetLevels(levels, BEAT_N_OSC);
}

void Beat::SetBPM(uint16_t bpm) {
    bpm_ = bpm;
    samples_per_beat_ = ((sample_rate_ * 60) / bpm);
}

void Beat::SetDownbeat(uint8_t downbeat) {
    downbeat_ = downbeat;
    if (downbeat_ == 0) {
        osc_set_freq(UPBEAT_FREQ);
    } else {
        osc_set_freq(DOWNBEAT_FREQ);
    }
}

void Beat::Fill(int16_t* buffer, size_t frames, uint8_t channel_count) {
    for (size_t i = 0; i < frames; i++) {
        for (size_t j = 0; j < channel_count; j++) {
            int16_t sample = envelope_.Apply(mixer_.Value());
            buffer[i*channel_count+j] = sample;
        }

        for (size_t j = 0; j < BEAT_N_OSC; j++) {
            osc_[j].Tick();
        }
        
        phase_++;

        if (phase_ % samples_per_beat_ == 0) {
            trigger_beat();
        }

        if (phase_ % samples_per_control_ == 0) {
            envelope_.Tick();
        }
    }
}

void Beat::trigger_beat() {
    envelope_.Reset();
    total_beats_++;
    if (downbeat_ != 0) {
        if (total_beats_ % downbeat_ == 0) {
            osc_set_freq(DOWNBEAT_FREQ);
        } else if (total_beats_ % downbeat_ == 1) {
            osc_set_freq(UPBEAT_FREQ);
        }
    }
}

void Beat::osc_set_freq(uint16_t freq) {
    for (size_t i = 0; i < BEAT_N_OSC; i++) {
        const size_t octave_step = i + 1;
        osc_[i].set_freq(freq / octave_step);
    }
}

const BeatMonitor& Beat::GetMonitor() {
    return monitor_;
}

BeatMonitor::BeatMonitor(uint32_t* total_beats)
    : total_beats_(total_beats) { }

uint32_t BeatMonitor::GetTotalBeats() const {
    return *total_beats_;
}

}
