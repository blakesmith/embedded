#ifndef KEEBIRD_INPUT_EVENT_H_
#define KEEBIRD_INPUT_EVENT_H_

#include "../synth/note.h"

namespace keebird {

enum InputEventType {
    NONE,
    BUTTON_DOWN,
    NOTE_DOWN,
};

class InputEvent {
public:
    InputEvent(InputEventType type);
    InputEvent(InputEventType type, char key_sym);
    InputEvent(InputEventType type, const Note* note);

    InputEvent(const InputEvent& other) = default;
    InputEvent(InputEvent&& other) = default;
    ~InputEvent() = default;
    InputEvent& operator=(const InputEvent& other) = default;

    InputEventType get_type() const;
    char get_key_sym() const;
    const Note* get_note() const;

private:
    InputEventType type_;

    union {
        char key_sym;
        const Note* note;
    } event_data_;
};

}

#endif
