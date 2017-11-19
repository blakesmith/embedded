#include "drivers/stm32/rtc.h"

stm32::RTClock rtc;

void Init() {
    rtc.Init();
}

int main() {
    Init();
    
    while (true) {
    }
}
