#ifndef KEEBEE_KEY_PIPELINE_H_
#define KEEBEE_KEY_PIPELINE_H_

#include "layout.h"
#include "usb_keyboard.h"

class KeyPipeline {
public:
    KeyPipeline(Layout* layout);
    KeyPipeline();
    ~KeyPipeline() = default;

    void SetLayout(Layout* layout);
    const USBKeyboard::HIDReport* MapKeyScans(bool* key_scans, uint16_t key_count);

private:
    Layout* current_layout_;
    uint8_t current_layer_index_;

    USBKeyboard::HIDReport reports_[2];
    USBKeyboard::HIDReport* current_report_;
    USBKeyboard::HIDReport* last_report_;

    bool map_modifiers(const Layer::Key& key, USBKeyboard::HIDReport* report);
    bool map_control_keys(const Layer::Key& key, bool key_scan);

    void switch_layer(uint8_t layer_index);
    void switch_layout(uint8_t layout_index);
    void reset_layer();
};

#endif
