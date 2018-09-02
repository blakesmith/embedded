#include "x11_display.h"

#include <cstdio>

namespace keebird {

X11Display::X11Display(const uint16_t display_width,
                       const uint16_t display_height)
    : display_width_(display_width),
      display_height_(display_height),
      display_(nullptr),
      screen_(-1)
{ }

int X11Display::Start() {
    printf("X11: Opening display\n");
    display_ = XOpenDisplay(static_cast<char*>(0));
    if (display_ == nullptr) {
        printf("Failed to open X11 display!\n");
        return -1;
    }
    screen_ = DefaultScreen(display_);

    // TODO: Erro handling?
    window_ = XCreateSimpleWindow(display_,
                                  DefaultRootWindow(display_),
                                  0,
                                  0,
                                  display_width_,
                                  display_height_,
                                  5,
                                  BlackPixel(display_, screen_),
                                  WhitePixel(display_, screen_));
    return 0;
}

void X11Display::Stop() {
    printf("X11: Destroying window\n");
    XDestroyWindow(display_, window_);
    if (display_ != nullptr) {
        printf("X11: Closing display\n");
        XCloseDisplay(display_);
    }
}

}

