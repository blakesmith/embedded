#ifndef KEEBEE_USB_KEEBOARD_H_
#define KEEBEE_USB_KEEBOARD_H_

#include "hid/usbd_hid.h"
#include "layout.h"

class USBKeyboard {
public:
    static constexpr uint8_t REPORT_BUF_SIZE = 8;
    struct HIDReport {
        HIDReport() : modifiers(0),
                      keys { 0, 0, 0, 0, 0, 0 } { }
        uint8_t modifiers;
        uint8_t keys[6];

        bool operator==(const HIDReport& rhs) const;
        bool operator!=(const HIDReport& rhs) const;

        void Reset() {
            modifiers = 0;
            keys[0] = 0;
            keys[1] = 0;
            keys[2] = 0;
            keys[3] = 0;
            keys[4] = 0;
            keys[5] = 0;
        }

        int Fill(uint8_t* buf, uint16_t size) const;
    };

    void Init();
    void SendReport(const HIDReport* report);
    void SendNullReport();
    void SendKeyScan(bool* key_scans, uint16_t key_count);

    USBKeyboard(Layout& layout);
    USBKeyboard();
    ~USBKeyboard() = default;

private:
    Layout current_layout_;

    __ALIGN_BEGIN uint8_t report_buf_[REPORT_BUF_SIZE] __ALIGN_END;
    USBD_HandleTypeDef usbd_device_;
    HIDReport reports_[2];
    HIDReport* current_report_;
    HIDReport* last_report_;

    void init_clock();
    void init_usb_device();
};

#endif
