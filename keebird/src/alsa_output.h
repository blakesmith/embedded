#ifndef KEEBIRD_ALSA_OUTPUT_H_
#define KEEBIRD_ALSA_OUTPUT_H_

#include <alsa/asoundlib.h>
#include <cstdint>
#include <cstddef>

namespace keebird {

class AlsaOutput {
public:
    AlsaOutput(uint32_t sample_rate);
    ~AlsaOutput() = default;

    int Start();
    void Stop();
    int Write(const int16_t* pcm_buf, size_t size);
private:
    snd_pcm_t* pcm_device_;
    const char* device_name_ = "hw:0,0";
    const uint32_t sample_rate_;
};

}

#endif
