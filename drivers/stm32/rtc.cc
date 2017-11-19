#include "rtc.h"

#include "stm32l1xx_pwr.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_rtc.h"

namespace stm32 {

void RTClock::Init() {
    RTC_InitTypeDef rcc_init;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_RTCAccessCmd(ENABLE);
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);

    RTC_StructInit(&rcc_init);
    rcc_init.RTC_HourFormat = RTC_HourFormat_24;
    rcc_init.RTC_AsynchPrediv = 0x7FF;
    rcc_init.RTC_SynchPrediv = 0xFF;
    RTC_Init(&rcc_init);
}

}
