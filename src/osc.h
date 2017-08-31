#ifndef NOME_OSC_H_
#define NOME_OSC_H_

#include <cstdint>

namespace nome {

class Osc {
public:
    Osc(const uint32_t sample_rate,
        const uint32_t control_rate);
    
    ~Osc() = default;
    
private:
    const uint32_t sample_rate_;
    const uint32_t control_rate_;

    uint32_t phase_;
};

}

#endif
