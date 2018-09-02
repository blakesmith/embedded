#include "input_event.h"

namespace keebird {

InputEvent::InputEvent(InputEventType type)
    : type_(type)
{ }

InputEvent::InputEvent(InputEventType type,
                       char key_sym)
    : type_(type) {
    event_data_.key_sym = key_sym;
}

InputEventType InputEvent::get_type() const {
    return type_;
}

char InputEvent::get_key_sym() const {
    if (type_ != InputEventType::BUTTON_DOWN) {
        return 0;
    } else {
        return event_data_.key_sym;
    }
}

}
