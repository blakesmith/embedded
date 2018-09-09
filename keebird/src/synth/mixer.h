#ifndef SYNTH_MIXER_H_
#define SYNTH_MIXER_H_

#include <assert.h>
#include <string.h>

namespace synth {

template <size_t MIXER_SIZE>
class Mixer {
public:
    Mixer() = default;
    
    int16_t Value() {
        int16_t value = 0;

        for (size_t i = 0; i < MIXER_SIZE; i++) {
            value += (static_cast<int32_t>(input_buffer_[i]) * levels_[i]) >> 8;
        }

        return value;
    }

    void set_levels(uint8_t* levels, size_t size) {
        assert(size == MIXER_SIZE);

        memcpy(levels_, levels, size * sizeof(uint8_t));
    }

    void set_input(int16_t value, size_t pos) {
        assert(pos < MIXER_SIZE);

        input_buffer_[pos] = value;
    }

private:
    uint8_t levels_[MIXER_SIZE];
    int16_t input_buffer_[MIXER_SIZE];
};

}

#endif
