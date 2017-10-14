#include <cstddef>

#include "cs43l22_dac.h"
#include "pec11_renc.h"
#include "ht16K33_display.h"
#include "status_led.h"

#include "beat.h"

using namespace nome;

static constexpr uint32_t SAMPLE_RATE = 44100;
static constexpr uint32_t CONTROL_RATE = SAMPLE_RATE / 10;
static constexpr uint8_t CHANNEL_COUNT = 2;

static constexpr size_t FRAMES_PER_PERIOD = 128;
static constexpr uint16_t DEFAULT_BPM = 120;
static constexpr uint8_t DEFAULT_DOWNBEAT = 4;

CS43L22Dac dac;
StatusLed status_led;
HT16K33Display display;
Pec11RotaryEncoder knob;

Beat beat(SAMPLE_RATE, CONTROL_RATE, DEFAULT_BPM, DEFAULT_DOWNBEAT);

void FillCallback(CS43L22Dac::Frame* frames, size_t n_frames, size_t buf_size) {
    beat.Fill((int16_t *)frames, n_frames, CHANNEL_COUNT);
}

static uint16_t current_bpm = 0;

void Init() {
    status_led.Init();
    display.Init();
    knob.Init();
    dac.Init(128, SAMPLE_RATE, &FillCallback);
    dac.Start();
}

void update_bpm() {
    knob.ReadState();
    if (knob.GetButtonAction() == BUTTON_ACTION_UP) {
        knob.ResetCount();
    }
    if (current_bpm != DEFAULT_BPM + knob.GetCount()) {
        current_bpm = DEFAULT_BPM + knob.GetCount();
        display.Clear();
        display.SetNumber(current_bpm);
        display.WriteDisplay();
        beat.SetBPM(current_bpm);
    }
}

int main() {
    Init();
    status_led.SetOk(true);

    while (true) {
        update_bpm();
    }
}
