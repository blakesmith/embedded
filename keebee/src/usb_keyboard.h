#ifndef KEEBEE_USB_KEEBOARD_H_
#define KEEBEE_USB_KEEBOARD_H_

#include "hid/usbd_hid.h"

class USBKeyboard {
public:
    static constexpr uint8_t REPORT_BUF_SIZE = 8;
    struct HIDReport {
        HIDReport() : modifiers(0),
                      key1(0),
                      key2(0),
                      key3(0),
                      key4(0),
                      key5(0),
                      key6(0) { }
        uint8_t modifiers;
        uint8_t key1;
        uint8_t key2;
        uint8_t key3;
        uint8_t key4;
        uint8_t key5;
        uint8_t key6;
    };

    void Init();
    void SendReport(const HIDReport* report);
    void SendNullReport();

private:
    __ALIGN_BEGIN uint8_t report_buf_[REPORT_BUF_SIZE] __ALIGN_END;
    USBD_HandleTypeDef usbd_device_;

    void init_clock();
    void init_usb_device();
};

#endif
