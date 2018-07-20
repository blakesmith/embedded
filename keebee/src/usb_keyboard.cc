#include "usb_keyboard.h"

#include "hid/usbd_desc.h"

#include "stm32f0xx_hal_flash.h"
#include "stm32f0xx_hal_rcc.h"

static constexpr uint16_t USBD_VID = 0xb38; // Vendor ID
static constexpr uint16_t USBD_PID = 0x0003; // Product id
static constexpr uint16_t USBD_LANG_ID = 0x409; // English, United States

static const uint8_t USBD_DeviceDesc[USB_LEN_DEV_DESC] = {
    0x12, // Size of descriptor in bytes
    USB_DESC_TYPE_DEVICE, // Device descriptor, constant
    0x00, // USB specification number, byte 1
    0x02, // USB specification number, byte 2
    0x03, // USB device class, HID is 3
    0x01, // USB device subclass, boot device
    0x01, // USB protocol, keyboard protocol
    USB_MAX_EP0_SIZE, // USB max packet size for zero endpoint,
    LOBYTE(USBD_VID), // USB id vendor, byte 1
    HIBYTE(USBD_VID), // USB id vendor, byte 2
    LOBYTE(USBD_PID), // USB product vendor, byte 1
    HIBYTE(USBD_PID), // USB product vendor, byte 2
    0x00, // USB spec version, set 2.0, byte 1
    0x02, // USB spec version, set 2.0, byte 2
    USBD_IDX_MFC_STR, // Index of manufacturer string
    USBD_IDX_PRODUCT_STR, // Index of product string
    USBD_IDX_SERIAL_STR, // Index of serial number string
    USBD_MAX_NUM_CONFIGURATION  // Number of possible configurations
};

static uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ];

static uint8_t USBD_StringSerial[USB_SIZ_STRING_SERIAL] = {
    USB_SIZ_STRING_SERIAL,
    USB_DESC_TYPE_STRING,
};

static const uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] = {
    USB_LEN_LANGID_STR_DESC,
    USB_DESC_TYPE_STRING,
    LOBYTE(USBD_LANG_ID),
    HIBYTE(USBD_LANG_ID),
};

static void int_to_unicode (uint32_t value , uint8_t *pbuf , uint8_t len) {
    uint8_t idx = 0;
  
    for( idx = 0 ; idx < len ; idx ++) {
        if(((value >> 28)) < 0xA) {
            pbuf[ 2* idx] = (value >> 28) + '0';
        } else {
            pbuf[2* idx] = (value >> 28) + 'A' - 10; 
        }
        value = value << 4;
        pbuf[ 2* idx + 1] = 0;
    }
}

static void set_serial_number(uint8_t* serial_buf) {
    uint32_t deviceserial0, deviceserial1, deviceserial2;
  
    deviceserial0 = *(uint32_t*)DEVICE_ID1;
    deviceserial1 = *(uint32_t*)DEVICE_ID2;
    deviceserial2 = *(uint32_t*)DEVICE_ID3;
  
    deviceserial0 += deviceserial2;
  
    if (deviceserial0 != 0) {
        int_to_unicode(deviceserial0, USBD_StringSerial,8);
        int_to_unicode(deviceserial1, &USBD_StringSerial[16], 4);
    }
}

static uint8_t* USBD_HID_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    *length = sizeof(USBD_DeviceDesc);
    return (uint8_t *)USBD_DeviceDesc;
}

static uint8_t* USBD_HID_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    *length = sizeof(USBD_LangIDDesc);
    return (uint8_t *)USBD_LangIDDesc;
}

static uint8_t* USBD_HID_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    USBD_GetString((uint8_t *)"KeeBee", USBD_StrDesc, length);
    return USBD_StrDesc;
}

static uint8_t* USBD_HID_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    USBD_GetString((uint8_t *)"KeeBee USB Keyboard", USBD_StrDesc, length);
    return USBD_StrDesc;
}

static uint8_t* USBD_HID_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length) {
    *length = USB_SIZ_STRING_SERIAL;

    set_serial_number(&USBD_StringSerial[2]);

    return USBD_StringSerial;
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
    USBD_HID_DeviceDescriptor,
    USBD_HID_LangIDStrDescriptor,
    USBD_HID_ManufacturerStrDescriptor,
    USBD_HID_ProductStrDescriptor,
    USBD_HID_SerialStrDescriptor,
    USBD_HID_ConfigStrDescriptor,
    USBD_HID_InterfaceStrDescriptor,
};

void USBKeyboard::Init() {
    init_clock();
    init_usb_device();
}

void USBKeyboard::SendReport(const HIDReport* report) {
    report_buf_[0] = report->modifiers;
    report_buf_[1] = 0;
    report_buf_[2] = report->keys[0];
    report_buf_[3] = report->keys[1];
    report_buf_[4] = report->keys[2];
    report_buf_[5] = report->keys[3];
    report_buf_[6] = report->keys[4];
    report_buf_[7] = report->keys[5];
    USBD_HID_SendReport(&usbd_device_, report_buf_, REPORT_BUF_SIZE);
}

void USBKeyboard::SendNullReport() {
    HIDReport report;
    SendReport(&report);
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
