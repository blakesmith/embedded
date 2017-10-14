#include <cstddef>

#include "cs43l22_dac.h"

#include "beat.h"
#include "settings.h"
#include "user_interface.h"

using namespace nome;

CS43L22Dac dac;
Settings settings;
UserInterface user_interface(settings);

Beat beat(settings.sample_rate,
          settings.control_rate,
          settings.current_bpm,
          settings.current_downbeat);

void FillCallback(CS43L22Dac::Frame* frames, size_t n_frames, size_t buf_size) {
    beat.Fill((int16_t *)frames, n_frames, settings.channel_count);
}

void Init() {
    user_interface.Init();
    dac.Init(settings.current_volume, settings.sample_rate, &FillCallback);
    dac.Start();
}

void loop() {
    switch (user_interface.Update()) {
        case UI_REFRESH_BPM:
            beat.SetBPM(settings.current_bpm);
            break;
        case UI_REFRESH_DOWNBEAT:
            beat.SetDownbeat(settings.current_downbeat);
            break;
        case UI_REFRESH_VOLUME:
        case UI_REFRESH_NONE:
            break;
    }
}

int main() {
    Init();
    user_interface.SetOk(true);

    while (true) {
        loop();
    }
}
