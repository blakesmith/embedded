#include "settings.h"

namespace nome {

Settings::Settings()
    : sample_rate(44100),
      control_rate(sample_rate / 10),
      channel_count(2),
      frames_per_period(128),
      current_bpm(120),
      current_downbeat(4),
      current_volume(128) { }
}
