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
                       const synth::Note* note)
    : type_(type) {
    event_data_.note = note;
}

bool InputEvent::operator==(const InputEvent& other) const {
    switch (type_) {
        case BUTTON_DOWN:
            return other.type_ == BUTTON_DOWN &&
                this->event_data_.key_sym == other.event_data_.key_sym;
        case NOTE_DOWN:
            return other.type_ == NOTE_DOWN &&
                this->event_data_.note == other.event_data_.note;
        case NOTE_UP:
            return other.type_ == NOTE_UP &&
                this->event_data_.note == other.event_data_.note;
        case NONE:
            return other.type_ == NONE;
        default:
            return false;
    }
}

bool InputEvent::operator!=(const InputEvent& other) const {
    return !(*this == other);
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

const synth::Note* InputEvent::get_note() const {
    if (type_ == InputEventType::NOTE_DOWN ||
        type_ == InputEventType::NOTE_UP) {
        return event_data_.note;
    } else {
        return synth::Note::ByIndex(0);
    }
}

}
