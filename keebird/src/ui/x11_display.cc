#include "x11_display.h"
#include "../util/log.h"

#include <X11/XKBlib.h>

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
    keebird_log_verbose("X11", "Opening display\n");
    display_ = XOpenDisplay(nullptr);
    if (display_ == nullptr) {
        keebird_log_verbose("X11", "Failed to open X11 display!\n");
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
                 StructureNotifyMask | KeyPressMask | KeyReleaseMask);

    if (XkbSetDetectableAutoRepeat(display_, true, nullptr)) {
        keebird_log_verbose("X11", "Disabled auto key repeat\n");
    } else {
        keebird_log_verbose("X11", "Warning! Unable to disable auto key repeat!\n");
    }

    keebird_log_verbose("X11", "Creating GC\n");
    gc_ = XCreateGC(display_, window_, 0, 0);

    XSetBackground(display_, gc_, WhitePixel(display_, screen_));
    XSetForeground(display_, gc_, BlackPixel(display_, screen_));

    XClearWindow(display_, window_);
    XMapWindow(display_, window_);

    return 0;
}

InputEvent X11Display::Poll() {
    XEvent ev;
    XNextEvent(display_, &ev);

    return input_.Translate(&ev);
}

void X11Display::Stop() {
    keebird_log_verbose("X11", "Freeing GC\n");
    XFreeGC(display_, gc_);
    keebird_log_verbose("X11", "Destroying window\n");
    XDestroyWindow(display_, window_);
    if (display_ != nullptr) {
        keebird_log_verbose("X11", "Closing display\n");
        XCloseDisplay(display_);
    }
}

}

