#include "usb_keyboard.h"

#include "stm32f0xx_hal_flash.h"
#include "stm32f0xx_hal_rcc.h"

static uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ];

static uint8_t* USBD_HID_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    USBD_GetString((uint8_t *)"KeeBee", USBD_StrDesc, length);
    return USBD_StrDesc;
}

static uint8_t* USBD_HID_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    USBD_GetString((uint8_t *)"KeeBee USB Keyboard", USBD_StrDesc, length);
    return USBD_StrDesc;
}

static uint8_t* USBD_HID_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    USBD_GetString((uint8_t *)"KeeBee HID Config", USBD_StrDesc, length);
    return USBD_StrDesc;
}

static uint8_t* USBD_HID_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    USBD_GetString((uint8_t *)"KeeBee HID Interface", USBD_StrDesc, length);
    return USBD_StrDesc;
}

static USBD_DescriptorsTypeDef hid_descriptors = {
    NULL,
    NULL,
    USBD_HID_ManufacturerStrDescriptor,
    USBD_HID_ProductStrDescriptor,
    NULL,
    USBD_HID_ConfigStrDescriptor,
    USBD_HID_InterfaceStrDescriptor,
};

void USBKeyboard::Init() {
    init_clock();
    init_usb_device();
}

void USBKeyboard::init_clock() {
    RCC_ClkInitTypeDef clock_init;
    RCC_OscInitTypeDef osc_init;
    RCC_PeriphCLKInitTypeDef periph_clock_init;
    RCC_CRSInitTypeDef crs_init;

    // Enable the HSI48 oscillator, and use it as the system clock source
    osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
    HAL_RCC_OscConfig(&osc_init);

    // Select HSI48 as the USB clock source
    periph_clock_init.PeriphClockSelection = RCC_PERIPHCLK_USB;
    periph_clock_init.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    HAL_RCCEx_PeriphCLKConfig(&periph_clock_init);

    // Select HSI48 as the system clock source, and configure HCLK and PCLK1 clock dividers
    clock_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1;
    clock_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
    clock_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clock_init.APB1CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&clock_init, FLASH_LATENCY_1);

    // Enable CRS clock
    __HAL_RCC_CRS_CLK_ENABLE();

    crs_init.Prescaler = RCC_CRS_SYNC_DIV1;
    crs_init.Source = RCC_CRS_SYNC_SOURCE_USB;
    crs_init.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
    crs_init.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;
    crs_init.HSI48CalibrationValue = 0x20;

    // Start CRS automatic synchronization
    HAL_RCCEx_CRSConfig(&crs_init);
    
    // Enable power controller clock
    __HAL_RCC_PWR_CLK_ENABLE();
}

void USBKeyboard::init_usb_device() {
    USBD_Init(&usbd_device_, &hid_descriptors, 0);
    USBD_RegisterClass(&usbd_device_, &USBD_HID);
    USBD_Start(&usbd_device_);
}
