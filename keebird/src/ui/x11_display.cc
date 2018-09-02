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
    display_ = XOpenDisplay(nullptr);
    if (display_ == nullptr) {
        printf("Failed to open X11 display!\n");
        return -1;
    }
    screen_ = DefaultScreen(display_);

    // TODO: Error handling?
    window_ = XCreateSimpleWindow(display_,
                                  DefaultRootWindow(display_),
                                  0,
                                  0,
                                  display_width_,
                                  display_height_,
                                  2,
                                  WhitePixel(display_, screen_),
                                  BlackPixel(display_, screen_));
    XSetStandardProperties(display_,
                           window_,
                           "Keebird",
                           "Keebird",
                           None,
                           nullptr,
                           0,
                           nullptr);
    XSelectInput(display_,
                 window_,
                 StructureNotifyMask | ButtonPressMask | KeyPressMask);

    printf("X11: Creating GC\n");
    gc_ = XCreateGC(display_, window_, 0, 0);

    XSetBackground(display_, gc_, WhitePixel(display_, screen_));
    XSetForeground(display_, gc_, BlackPixel(display_, screen_));

    XClearWindow(display_, window_);
    XMapWindow(display_, window_);

    XEvent ev;
    XNextEvent(display_, &ev);

    return 0;
}

void X11Display::Stop() {
    printf("X11: Freeing GC\n");
    XFreeGC(display_, gc_);
    printf("X11: Destroying window\n");
    XDestroyWindow(display_, window_);
    if (display_ != nullptr) {
        printf("X11: Closing display\n");
        XCloseDisplay(display_);
    }
}

}

