#include "alsa_output.h"

namespace nome {

AlsaOutput::AlsaOutput(uint32_t sample_rate)
    : sample_rate_(sample_rate) { }

int AlsaOutput::Start() {
    int rc;
    snd_pcm_hw_params_t *hw_params;

    printf("ALSA: Opening PCM playback device: %s\n", device_name_);
    rc = snd_pcm_open(&pcm_device_, device_name_, SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0) {
        printf("ALSA: Failed to open PCM playback device: %s\n", snd_strerror(rc));
        return rc;
    }
    rc = snd_pcm_hw_params_malloc(&hw_params);
    if (rc < 0) {
        printf("ALSA: Failed to allocate hardware params: %s\n", snd_strerror(rc));
        return rc;
    }
    rc = snd_pcm_hw_params_any(pcm_device_, hw_params);
    if (rc < 0) {
        printf("ALSA: Failed to initialize hardware structure: %s\n", snd_strerror(rc));
        return rc;
    }
    rc = snd_pcm_hw_params_set_access(pcm_device_, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (rc < 0) {
        printf("ALSA: Failed to set device access: %s\n", snd_strerror(rc));
        return rc;
    }
    rc = snd_pcm_hw_params_set_format(pcm_device_, hw_params, SND_PCM_FORMAT_S16_LE);
    if (rc < 0) {
        printf("ALSA: Failed to set sample format: %s\n", snd_strerror(rc));
        return rc;
    }
    rc = snd_pcm_hw_params_set_rate_near(pcm_device_, hw_params, const_cast<unsigned int*>(&sample_rate_), 0);
    if (rc < 0) {
        printf("ALSA: Failed to set sample rate: %s\n", snd_strerror(rc));
        return rc;
    }
    rc = snd_pcm_hw_params_set_period_size(pcm_device_, hw_params, 128, 0);
    if (rc < 0) {
        printf("ALSA: Failed to set period size: %s\n", snd_strerror(rc));
        return rc;
    }
    rc = snd_pcm_hw_params_set_channels(pcm_device_, hw_params, 2);
    if (rc < 0) {
        printf("ALSA: Failed to set channel count: %s\n", snd_strerror(rc));
        return rc;
    }
    rc = snd_pcm_hw_params(pcm_device_, hw_params);
    if (rc < 0) {
        printf("ALSA: Cannot set parameters: %s\n", snd_strerror(rc));
        return rc;
    }

    snd_pcm_hw_params_free(hw_params);

    rc = snd_pcm_prepare(pcm_device_);
    if (rc < 0) {
        printf("ALSA: Failed to prepare device for use: %s\n", snd_strerror(rc));
        return rc;
    }

    snd_pcm_uframes_t frames;

    snd_pcm_hw_params_get_period_size(hw_params, &frames, 0);

    printf("ALSA: period size: %lu\n", frames);

    return 0;
}

void AlsaOutput::Stop() {
    int rc;

    printf("ALSA: Closing playback device: %s\n", device_name_);
    if (pcm_device_ != nullptr) {
        snd_pcm_drain(pcm_device_);
        rc = snd_pcm_close(pcm_device_);
        if (rc < 0) {
            printf("ALSA: Warning, failed to close device: %s\n", snd_strerror(rc));
        }
    }
}

int AlsaOutput::Write(const int16_t* pcm_buf, size_t size) {
    snd_pcm_sframes_t written = snd_pcm_writei(pcm_device_, pcm_buf, size);
    if (written < 0) {
        printf("ALSA: Failed to write, %s\n", snd_strerror(written));
        return written;
    }
    
    return 0;
}

}
