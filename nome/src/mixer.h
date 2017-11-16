#ifndef NOME_MIXER_H_
#define NOME_MIXER_H_

#include <assert.h>
#include <string.h>

#include "osc.h"

namespace nome {

template <size_t MIXER_SIZE>
class Mixer {
public:
    Mixer(Osc* oscs, size_t size) {
        assert(size == MIXER_SIZE);

        for (size_t i = 0; i < size; i++) {
            oscs_[i] = &oscs[i];
        }
    }
    
    void SetLevels(uint8_t* levels, size_t size) {
        assert(size == MIXER_SIZE);
        
        memcpy(levels_, levels, size * sizeof(uint8_t));
    }
    
    int16_t Value() {
        int16_t value = 0;

        for (size_t i = 0; i < MIXER_SIZE; i++) {
            value += (static_cast<int32_t>(oscs_[i]->Value()) * levels_[i]) >> 8;
        }

        return value;
    }

private:
    Osc* oscs_[MIXER_SIZE];
    uint8_t levels_[MIXER_SIZE];
};

}

#endif
