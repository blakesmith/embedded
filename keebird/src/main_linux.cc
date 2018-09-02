#include <atomic>
#include <cstdio>
#include <thread>

#include "alsa_output.h"
#include "audio_pipeline.h"
#include "ui/input_event.h"
#include "ui/ui.h"

using namespace keebird;

static constexpr uint32_t SAMPLE_RATE = 44100;
static constexpr uint32_t CONTROL_RATE = SAMPLE_RATE / 10;
static constexpr uint8_t CHANNEL_COUNT = 2;
static constexpr size_t FRAMES_PER_PERIOD = 128;
static constexpr uint16_t DEFAULT_BPM = 120;
static constexpr uint8_t DEFAULT_DOWNBEAT = 4;
static constexpr uint16_t DISPLAY_WIDTH = 160;
static constexpr uint16_t DISPLAY_HEIGHT = 128;

std::atomic<bool> should_run(true);

void audio_thread_main(AudioPipeline* pipeline, AlsaOutput* sound_out) {
    int16_t sample_buffer[FRAMES_PER_PERIOD*CHANNEL_COUNT];

    while (should_run.load()) {
        pipeline->Fill(sample_buffer, FRAMES_PER_PERIOD, CHANNEL_COUNT);
        sound_out->Write(sample_buffer, FRAMES_PER_PERIOD);
    }
}

void ui_thread_main(Ui* ui) {
    while (should_run.load()) {
        InputEvent event = ui->Poll();
        switch (event.get_type()) {
            case InputEventType::BUTTON_DOWN: {
                printf("Got key: %c\n", event.get_key_sym());
                if (event.get_key_sym() == 'q') {
                    should_run.store(false);
                }
                break;
            }
            default:
                continue;
        }
    }
}

int main(int argc, char** argv) {
    int rc;
    Ui ui(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    AudioPipeline pipeline(SAMPLE_RATE, CONTROL_RATE);
    AlsaOutput sound_out(SAMPLE_RATE);

    rc = sound_out.Start();
    if (rc < 0) {
        printf("Failed to open sound playback device!\n");
        return rc;
    }

    rc = ui.Start();
    if (rc < 0) {
        printf("Failed to start UI!\n");
        return rc;
    }

    std::thread audio_thread(audio_thread_main, &pipeline, &sound_out);
    std::thread ui_thread(ui_thread_main, &ui);

    audio_thread.join();
    ui_thread.join();

    sound_out.Stop();
    ui.Stop();
    
    return 0;
}

