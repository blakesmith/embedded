#ifndef KEEBIRD_INPUT_EVENT_H_
#define KEEBIRD_INPUT_EVENT_H_

namespace keebird {

enum InputEventType {
    NONE,
    BUTTON_DOWN,
};

class InputEvent {
public:
    InputEvent(InputEventType type);
    InputEvent(const InputEvent& other) = default;
    InputEvent(InputEvent&& other) = default;
    ~InputEvent() = default;
    InputEvent& operator=(const InputEvent& other) = default;

    InputEventType get_type() const;

private:
    InputEventType type_;
};

}

#endif
