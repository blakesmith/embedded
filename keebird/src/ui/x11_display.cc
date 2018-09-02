#include "x11_display.h"

namespace keebird {

X11Display::X11Display(const uint16_t display_width,
                       const uint16_t display_height)
    : display_width_(display_width),
      display_height_(display_height)
{ }

int X11Display::Init() {
    return 0;
}

void X11Display::Stop() {
}

}

