#include "osc.h"

namespace nome {

Osc::Osc(const uint32_t sample_rate,
         const uint32_t control_rate)
    : sample_rate_(sample_rate),
      control_rate_(control_rate),
      phase_(0) { }

}
