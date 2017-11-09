#include "beat.h"

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
      osc_(OscShape::SIN, sample_rate, DOWNBEAT_FREQ, 50),
      envelope_(control_rate, 255, 1, 20, 0, 225, 0),
      monitor_(&total_beats_) {
    SetDownbeat(downbeat_);
}

void Beat::SetBPM(uint16_t bpm) {
    bpm_ = bpm;
    samples_per_beat_ = ((sample_rate_ * 60) / bpm);
}

void Beat::SetDownbeat(uint8_t downbeat) {
    downbeat_ = downbeat;
    if (downbeat_ == 0) {
        osc_.set_freq(UPBEAT_FREQ);
    } else {
        osc_.set_freq(DOWNBEAT_FREQ);
    }
}

void Beat::Fill(int16_t* buffer, size_t frames, uint8_t channel_count) {
    for (size_t i = 0; i < frames; i++) {
        for (size_t j = 0; j < channel_count; j++) {
            int16_t sample = (static_cast<int32_t>(osc_.Value()) * envelope_.Value()) >> 8;
            buffer[i*channel_count+j] = sample;
        }

        osc_.Tick();
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
            osc_.set_freq(DOWNBEAT_FREQ);
        } else if (total_beats_ % downbeat_ == 1) {
            osc_.set_freq(UPBEAT_FREQ);
        }
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
