#ifndef KEEBIRD_X11_DISPLAY_H_
#define KEEBIRD_X11_DISPLAY_H_

#include <cstdint>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

namespace keebird {

class X11Display {
public:
    X11Display(const uint16_t display_width,
               const uint16_t display_height);
    ~X11Display() = default;

    int Start();
    void Stop();

private:
    const uint16_t display_width_;
    const uint16_t display_height_;

    Display* display_;
    Window window_;
    GC gc_;
};

}

#endif
