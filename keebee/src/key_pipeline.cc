#include "key_pipeline.h"

KeyPipeline::KeyPipeline(Layout* layout) : current_layout_(layout),
                                                 current_layer_index_(0),
                                                 current_report_(&reports_[0]),
                                                 last_report_(&reports_[1]) { }

KeyPipeline::KeyPipeline() : current_layout_(const_cast<Layout*>(&DEFAULT_LAYOUT)),
                             current_layer_index_(0),
                             current_report_(&reports_[0]),
                             last_report_(&reports_[1]) { }

void KeyPipeline::SetLayout(Layout* layout) {
    if (layout == current_layout_) {
        return;
    } else {
        current_layout_ = layout;
    }
}

const USBKeyboard::HIDReport* KeyPipeline::MapKeyScans(bool* key_scans, uint16_t key_count) {
    uint8_t current_key = 0;
    bool control_key;
    USBKeyboard::HIDReport *report = current_report_;
    report->Reset();

    for (unsigned int i = 0; i < key_count; i++) {
        if (current_key == 5) {
            // No more keys left in the current HID report, send what we have.
            break;
        }

        const Layer::Key key = current_layout_->MapKey(current_layer_index_, i, key_count);
        const bool key_scan = key_scans[i];
        control_key = map_control_keys(key, key_scan);

        if (key_scan) {
            control_key = control_key || map_modifiers(key, report);

            if (!control_key) {
                report->keys[current_key] = key;
                current_key++;
            }
        }
    }

    bool new_report = report != last_report_;
    report = last_report_;
    last_report_ = current_report_;
    current_report_ = report;

    if (new_report) {
        return last_report_;
    } else {
        return nullptr;
    }
}

bool KeyPipeline::map_modifiers(const Layer::Key& key, USBKeyboard::HIDReport* report) {
    switch (key) {
        case KEY_LEFTCTRL: {
            report->modifiers |= USBKeyboard::MOD_LEFT_CTRL;
            return true;
        }
        case KEY_LEFTSHIFT: {
            report->modifiers |= USBKeyboard::MOD_LEFT_SHIFT;
            return true;
        }
        case KEY_LEFTALT: {
            report->modifiers |= USBKeyboard::MOD_LEFT_ALT;
            return true;
        }
        case KEY_LEFTMETA: {
            report->modifiers |= USBKeyboard::MOD_LEFT_META;
            return true;
        }
        case KEY_RIGHTCTRL: {
            report->modifiers |= USBKeyboard::MOD_RIGHT_CTRL;
            return true;
        }
        case KEY_RIGHTSHIFT: {
            report->modifiers |= USBKeyboard::MOD_RIGHT_SHIFT;
            return true;
        }
        case KEY_RIGHTALT: {
            report->modifiers |= USBKeyboard::MOD_RIGHT_ALT;
            return true;
        }
        case KEY_RIGHTMETA: {
            report->modifiers |= USBKeyboard::MOD_RIGHT_META;
            return true;
        }
        default:
            return false;
    }
}

bool KeyPipeline::map_control_keys(const Layer::Key& key, const bool key_scan) {
    const Layer::Key control_key = key & 0xff00; // Top 8 bits
    const uint8_t data = key & 0xff; // Bottom 8 bits
    switch (control_key) {
        case KB_LAYER_SHIFT: {
            key_scan ? switch_layer(data) : reset_layer();
            return true;
        }
        case KB_LAYOUT_SWITCH: {
            if (key_scan) {
                switch_layout(data);
            }
            return true;
        }
        default:
            return false;
    }
}

void KeyPipeline::switch_layer(uint8_t layer_index) {
    if (layer_index < 0 || layer_index > (current_layout_->layer_count - 1)) {
        return;
    }

    // Avoid fighting with layer combinations
    if (layer_index <= current_layer_index_) {
        return;
    }

    current_layer_index_ = layer_index;
}

void KeyPipeline::switch_layout(uint8_t layout_index) {
    if (layout_index < 0 || layout_index > (LAYOUT_COUNT - 1)) {
        return;
    }

    SetLayout(const_cast<Layout*>(&LAYOUTS[layout_index]));
}

void KeyPipeline::reset_layer() {
    current_layer_index_ = 0;
}

