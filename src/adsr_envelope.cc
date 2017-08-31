#include "adsr_envelope.h"

namespace nome {

AdsrEnvelope::AdsrEnvelope(const uint8_t attack,
                           const uint8_t decay,
                           const uint8_t sustain,
                           const uint8_t release)
    : attack_(attack),
      decay_(decay),
      sustain_(sustain),
      release_(release),
      phase_(0) { }
}
