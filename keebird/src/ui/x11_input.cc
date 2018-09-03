#include <X11/Xutil.h>

#include "x11_input.h"
#include <cstdio>

namespace keebird {

InputEvent X11Input::Translate(XEvent* event) {
    switch (event->type) {
        case KeyPress: {
            printf("Got keycode: %d\n", event->xkey.keycode);
            int len;
            char buf;
            KeySym sym;
            len = XLookupString(&event->xkey, &buf, 1, &sym, nullptr);
            if (len > 0) {
                if (buf == 'q') {
                    return InputEvent(InputEventType::BUTTON_DOWN, buf);
                } else {
                    return InputEvent(InputEventType::NOTE_DOWN,
                                      Note::ByIndex(event->xkey.keycode));
                }
            } else {
                return InputEvent(InputEventType::NONE);
            }

        }
        default:
            return InputEvent(InputEventType::NONE);
    }
}

}
