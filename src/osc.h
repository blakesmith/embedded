#ifndef NOME_OSC_H_
#define NOME_OSC_H_

#include <cstdint>

namespace nome {

enum OscShape {
    OSC_SHAPE_SIN
};

class Osc {
public:
    Osc(const OscShape shape,
        const uint16_t freq_hz,
        const uint8_t amplitude);

    ~Osc() = default;

    void Tick();
    int16_t Value();

private:
    const OscShape shape_;
    uint16_t freq_hz_;
    uint8_t amplitude_;

    uint32_t phase_;
};

}

#endif
