#include "adsr_envelope.h"
#include "osc.h"

using namespace nome;

static const uint32_t SAMPLE_RATE = 44100;
static const uint32_t CONTROL_RATE = SAMPLE_RATE / 10;

int main(int argc, char** argv) {
    Osc osc(OscShape::OSC_SHAPE_SIN, 440, 50);
    AdsrEnvelope envelope(1, 10, 0, 244);
    
    return 0;
}

