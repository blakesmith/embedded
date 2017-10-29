#include <cstddef>

#include "cs43l22_dac.h"

#include "beat.h"
#include "settings.h"
#include "user_interface.h"

using namespace nome;

Pinout pinout;
CS43L22Dac dac(pinout.i2c_bus, pinout.dac_reset);
Settings settings;
Beat beat(settings.GetSampleRate(),
          settings.GetControlRate(),
          settings.GetBPM(),
          settings.GetDownbeat());
UserInterface user_interface(settings, pinout, beat.GetMonitor());



static uint8_t scale_volume(uint8_t volume) {
    if (volume > 15) {
        volume = 11;
    }
    return volume * 13;
}

static void FillCallback(CS43L22Dac::Frame* frames, size_t n_frames, size_t buf_size) {
    beat.Fill((int16_t *)frames, n_frames, settings.GetChannelCount());
}

void Init() {
    pinout.Init();
    user_interface.Init();
    dac.Init(scale_volume(settings.GetVolume()),
             settings.GetSampleRate(),
             &FillCallback);
    dac.Start();
}

void loop() {
    switch (user_interface.Update()) {
        case UI_REFRESH_BPM:
            beat.SetBPM(settings.GetBPM());
            break;
        case UI_REFRESH_DOWNBEAT:
            beat.SetDownbeat(settings.GetDownbeat());
            break;
        case UI_REFRESH_VOLUME:
            dac.SetVolume(scale_volume(settings.GetVolume()));
            break;
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
