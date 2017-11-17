#include <cstdio>

#include "alsa_output.h"

#include "beat.h"

using namespace nome;

static const uint32_t SAMPLE_RATE = 44100;
static const uint32_t CONTROL_RATE = SAMPLE_RATE / 10;
static const uint8_t CHANNEL_COUNT = 2;
static const size_t FRAMES_PER_PERIOD = 128;
static const uint16_t DEFAULT_BPM = 120;
static const uint8_t DEFAULT_DOWNBEAT = 4;

int main(int argc, char** argv) {
    int rc;
    int16_t sample_buffer[FRAMES_PER_PERIOD*CHANNEL_COUNT];
    Beat beat(SAMPLE_RATE, CONTROL_RATE, DEFAULT_BPM, DEFAULT_DOWNBEAT);
    AlsaOutput sound_out(SAMPLE_RATE);

    rc = sound_out.Start();
    if (rc < 0) {
        printf("Failed to open sound playback device!\n");
        return rc;
    }

    uint32_t seconds = 5;
    uint32_t total_samples = SAMPLE_RATE * seconds;
    for (uint32_t current_samples = 0;
         current_samples < total_samples;
         current_samples += FRAMES_PER_PERIOD) {
        beat.Fill(sample_buffer, FRAMES_PER_PERIOD, CHANNEL_COUNT);
        sound_out.Write(sample_buffer, FRAMES_PER_PERIOD);
    }

    sound_out.Stop();
    
    return 0;
}

