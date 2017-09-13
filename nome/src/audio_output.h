#ifndef NOME_AUDIO_OUTPUT_H_
#define NOME_AUDIO_OUTPUT_H_

#include <cstddef>

class AudioOutput {
    virtual int Start() = 0;
    virtual void Stop() = 0;
    virtual int Write(const int16_t* pcm_buf, size_t size) = 0;
};

class NullAudioOutput : public AudioOutput {
public:
    int Start() { return 0; }
    void Stop() { }
    int Write(const int16_t* pcm_buf, size_t size) { return 0; }
};

#endif
