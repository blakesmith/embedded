#include "x11_input.h"

namespace keebird {

InputEvent X11Input::Translate(XEvent* event) {
    switch (event->type) {
        case KeyPress:
            return InputEvent(InputEventType::BUTTON_DOWN);
        default:
            return InputEvent(InputEventType::NONE);
    }
}

}
