#include <X11/Xutil.h>

#include "x11_input.h"
#include "../util/log.h"

#include <cstdio>

namespace keebird {

InputEvent X11Input::Translate(XEvent* event) {
    switch (event->type) {
        case KeyPress: {
            keebird_log_verbose("X11", "Got KeyPress: %d\n", event->xkey.keycode);
            int len;
            char buf;
            KeySym sym;
            len = XLookupString(&event->xkey, &buf, 1, &sym, nullptr);
            if (len > 0) {
                if (buf == 'q') {
                    return InputEvent(InputEventType::BUTTON_DOWN, buf);
                } else {
                    return InputEvent(InputEventType::NOTE_DOWN,
                                      synth::Note::ByIndex(event->xkey.keycode));
                }
            } else {
                return InputEvent(InputEventType::NONE);
            }

        }
        case KeyRelease: {
            keebird_log_verbose("X11", "Got KeyRelease: %d\n", event->xkey.keycode);
            return InputEvent(InputEventType::NOTE_UP,
                              synth::Note::ByIndex(event->xkey.keycode));
        }
        default:
            return InputEvent(InputEventType::NONE);
    }
}

}
