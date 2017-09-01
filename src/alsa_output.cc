#include "alsa_output.h"

namespace nome {

AlsaOutput::AlsaOutput(uint32_t sample_rate)
    : sample_rate_(sample_rate) { }

int AlsaOutput::Start() {
    return 0;
}

void AlsaOutput::Stop() {
}

int AlsaOutput::Write(const int16_t* pcm_buf, size_t size) {
    return 0;
}

}
