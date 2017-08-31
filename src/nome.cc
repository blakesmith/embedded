#include "osc.h"

using namespace nome;

static const uint32_t SAMPLE_RATE = 44100;
static const uint32_t CONTROL_RATE = SAMPLE_RATE / 10;

int main(int argc, char** argv) {
    Osc osc(SAMPLE_RATE, CONTROL_RATE);
    
    return 0;
}

