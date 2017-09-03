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
        const uint32_t sample_rate,
        const uint16_t freq_hz,
        const uint8_t amplitude);

    ~Osc() = default;

    void Tick();
    int16_t Value();

    void set_freq(uint16_t freq_hz);
    void compute_phase_increment();
    int16_t compute_next_value();

private:
    const OscShape shape_;
    const uint32_t sample_rate_;
    uint16_t freq_hz_;
    uint8_t amplitude_;

    int16_t value_;
    uint32_t phase_;
    uint32_t phase_increment_;
};

}

#endif
