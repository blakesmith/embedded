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

InputEvent::InputEvent(InputEventType type,
                       const Note* note)
    : type_(type) {
    event_data_.note = note;
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

const Note* InputEvent::get_note() const {
    if (type_ != InputEventType::NOTE_DOWN) {
        return Note::ByIndex(0);
    } else {
        return event_data_.note;
    }
}

}
