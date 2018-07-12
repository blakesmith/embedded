#ifndef KEEBEE_USB_KEEBOARD_H_
#define KEEBEE_USB_KEEBOARD_H_

#include "hid/usbd_hid.h"

class USBKeyboard {
public:
    void Init();

private:
    USBD_HandleTypeDef usbd_device_;

    void init_clock();
    void init_usb_device();
};

#endif
