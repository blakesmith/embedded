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

void RTClock::GetTime(Time* time) {
    RTC_TimeTypeDef get_time;

    RTC_GetTime(RTC_Format_BIN, &get_time);
    time->hour = get_time.RTC_Hours;
    time->minute = get_time.RTC_Minutes;
    time->second = get_time.RTC_Seconds;
    time->am_pm = get_time.RTC_H12 == RTC_H12_AM ? AM_PM::AM : AM_PM::PM;
}

void RTClock::SetTime(Time* time) {
    RTC_TimeTypeDef set_time;

    set_time.RTC_Hours = time->hour;
    set_time.RTC_Minutes = time->minute;
    set_time.RTC_Seconds = time->second;
    set_time.RTC_H12 = time->am_pm == AM_PM::AM ? RTC_H12_AM : RTC_H12_PM;
    RTC_SetTime(RTC_Format_BIN, &set_time);
}

}
