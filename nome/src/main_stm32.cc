#include <cstddef>

#include "cs43l22_dac.h"
#include "status_led.h"

#include "beat.h"

using namespace nome;

static constexpr uint32_t SAMPLE_RATE = 44100;
static constexpr uint32_t CONTROL_RATE = SAMPLE_RATE / 10;
static constexpr uint8_t CHANNEL_COUNT = 2;

static constexpr size_t FRAMES_PER_PERIOD = 128;
static constexpr uint16_t DEFAULT_BPM = 120;
static constexpr uint8_t DEFAULT_DOWNBEAT = 4;

StatusLed status_led;
Beat beat(SAMPLE_RATE, CONTROL_RATE, DEFAULT_BPM, DEFAULT_DOWNBEAT);

void FillCallback(CS43L22Dac::Frame* frames, size_t size) {
    status_led.SetActivity(true);
    beat.Fill((int16_t *)frames, size, CHANNEL_COUNT);
}

void Init() {
    status_led.Init();
    CS43L22Dac::GetGlobalInstance()->Init(128, SAMPLE_RATE, &FillCallback);
}

extern "C" {
void DMA1_Stream7_IRQHandler(void) {
    status_led.SetActivity(true);
    if (DMA_GetFlagStatus(DMA1_Stream7, DMA_FLAG_TEIF7) != RESET) {
        DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TEIF7);
        status_led.SetError(true);
    }
    
    if (DMA_GetFlagStatus(DMA1_Stream7, DMA_FLAG_TCIF7) != RESET) {
        DMA_ClearFlag(DMA1_Stream7, DMA_FLAG_TCIF7);

        CS43L22Dac::GetGlobalInstance()->FillTxBuffer();
    }
}
}

int main() {
    Init();
    CS43L22Dac::GetGlobalInstance()->Start();
    status_led.SetOk(true);

    while (true);
}
