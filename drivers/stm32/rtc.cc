#include "rtc.h"

#if defined(STM32F411xE) || defined(STM32F413_423xx)
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_rcc.h"
#endif

#ifdef STM32L1XX_MD
#include "stm32l1xx_pwr.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_rtc.h"
#endif


namespace stm32 {

RTClock::RTClock(const ClockSource clock_source)
    : clock_source_(clock_source)
{ }

bool RTClock::Init() {
    RTC_InitTypeDef rcc_init;

#ifdef STM32L1XX_MD
    RCC_RTCResetCmd(DISABLE);
#endif
#if defined(STM32F411xE) || defined(STM32F413_423xx)
    RCC_BackupResetCmd(DISABLE);
#endif

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    RTC_WriteProtectionCmd(DISABLE);

#ifdef STM32L1XX_MD
    PWR_RTCAccessCmd(ENABLE);
#endif
#if defined(STM32F411xE) || defined(STM32F413_423xx)
    PWR_BackupAccessCmd(ENABLE);
#endif

    if (clock_source_ == ClockSource::LSI) {
        RCC_LSICmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    } else {
        RCC_LSEConfig(RCC_LSE_ON);
        while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    }

    RTC_StructInit(&rcc_init);
    rcc_init.RTC_HourFormat = RTC_HourFormat_12;
    rcc_init.RTC_AsynchPrediv = GetAsynchPrediv();
    rcc_init.RTC_SynchPrediv = GetSynchPrediv();

    RCC_RTCCLKCmd(ENABLE);

    bool success = RTC_Init(&rcc_init) == SUCCESS;
    RTC_WriteProtectionCmd(ENABLE);
    return success;
}

void RTClock::GetTime(Time* time) {
    RTC_TimeTypeDef get_time;

    RTC_GetTime(RTC_Format_BIN, &get_time);
    time->subsecond = RTC_GetSubSecond();
    time->hour = get_time.RTC_Hours;
    time->minute = get_time.RTC_Minutes;
    time->second = get_time.RTC_Seconds;
    time->am_pm = get_time.RTC_H12 == RTC_H12_AM ? AM_PM::AM : AM_PM::PM;
}

bool RTClock::SetTime(Time* time) {
    RTC_TimeTypeDef set_time;

    set_time.RTC_Hours = time->hour;
    set_time.RTC_Minutes = time->minute;
    set_time.RTC_Seconds = time->second;
    set_time.RTC_H12 = time->am_pm == AM_PM::AM ? RTC_H12_AM : RTC_H12_PM;
    return RTC_SetTime(RTC_Format_BIN, &set_time) == SUCCESS;
}

uint32_t RTClock::GetSynchPrediv() const {
#if defined(STM32F411xE) || defined(STM32F413_423xx)
    if (clock_source_ == ClockSource::LSE) {
        return 0xFF;
    } else {
        return 0xF9;
    }
#endif
#ifdef STM32L1XX_MD
    if (clock_source_ == ClockSource::LSE) {
        return 0xFF;
    } else {
        return 0x127;
    }
#endif
}

uint32_t RTClock::GetAsynchPrediv() const {
#if defined(STM32F411xE) || defined(STM32F413_423xx)
    if (clock_source_ == ClockSource::LSE) {
        return 0x7F;
    } else {
        return 0x7F;
    }
#endif
#ifdef STM32L1XX_MD
    if (clock_source_ == ClockSource::LSE) {
        return 0x7F;
    } else {
        return 0x7C;
    }
#endif
}

}
