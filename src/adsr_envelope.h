#ifndef NOME_ADSR_ENVELOPE_H_
#define NOME_ADSR_ENVELOPE_H_

#include <cstdint>

namespace nome {

class AdsrEnvelope {
public:
    AdsrEnvelope(const uint8_t attack,
                 const uint8_t decay,
                 const uint8_t sustain,
                 const uint8_t release);

    ~AdsrEnvelope() = default;

    void Tick();
    double Value();

private:
    const uint32_t attack_;
    const uint32_t decay_;
    const uint32_t sustain_;
    const uint32_t release_;

    uint32_t phase_;
};
    
}

#endif
