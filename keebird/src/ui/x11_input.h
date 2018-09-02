#ifndef KEEBIRD_X11_INPUT_H_
#define KEEBIRD_X11_INPUT_H_

#include <X11/Xlib.h>

#include "input_event.h"

namespace keebird {

class X11Input {
public:
    InputEvent Translate(XEvent* ev);
};

}

#endif
