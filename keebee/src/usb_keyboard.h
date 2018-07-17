#ifndef KEEBEE_USB_KEEBOARD_H_
#define KEEBEE_USB_KEEBOARD_H_

#include "hid/usbd_hid.h"

class USBKeyboard {
public:
    struct HIDReport {
        uint8_t id;
        uint8_t modifiers;
        uint8_t reserved;
        uint8_t key1;
        uint8_t key2;
        uint8_t key3;
        uint8_t key4;
        uint8_t key5;
        uint8_t key6;
    };

    void Init();

private:
    USBD_HandleTypeDef usbd_device_;

    void init_clock();
    void init_usb_device();
};

#endif
