#include "osc.h"

namespace nome {

Osc::Osc(const OscShape shape,
         const uint16_t freq_hz,
         const uint8_t amplitude)
    : shape_(shape),
      freq_hz_(freq_hz),
      amplitude_(amplitude),
      phase_(0) { }
}
