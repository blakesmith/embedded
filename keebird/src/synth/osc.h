#ifndef SYNTH_OSC_H_
#define SYNTH_OSC_H_

#include <cstdint>
#include <cstddef>

namespace synth {

enum class OscShape {
    SIN,
    TRIANGLE,
    SQUARE
};

class Osc {
public:
    Osc(OscShape shape,
        const uint32_t sample_rate,
        const double freq_hz);

    ~Osc() = default;

    void Tick();
    int16_t Value();

    void set_freq(double freq_hz);
    void set_freq(uint16_t freq_hz);
    void set_shape(OscShape shape);

private:
    OscShape shape_;
    const uint32_t sample_rate_;
    double freq_hz_;

    int16_t value_;
    uint32_t phase_;
    uint32_t phase_increment_;

    size_t table_size_;
    int16_t *table_;

    void compute_phase_increment();
    void generate_square_table();
    void generate_triangle_table();
    void assign_lookup_table();
    int16_t compute_next_value();
};

}

#endif
