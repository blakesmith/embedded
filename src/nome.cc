#include "beat.h"

using namespace nome;

static const uint32_t SAMPLE_RATE = 44100;
static const uint32_t CONTROL_RATE = SAMPLE_RATE / 10;
static const size_t SAMPLE_BUFFER_SIZE = 128;

int main(int argc, char** argv) {
    int16_t sample_buffer[SAMPLE_BUFFER_SIZE];
    Beat beat(SAMPLE_RATE, CONTROL_RATE);

    uint32_t seconds = 1;
    uint32_t total_samples = SAMPLE_RATE * seconds;
    for (uint32_t current_samples = 0;
         current_samples < total_samples;
         current_samples += SAMPLE_BUFFER_SIZE) {
        beat.Fill(sample_buffer, SAMPLE_BUFFER_SIZE);
    }
    
    return 0;
}

