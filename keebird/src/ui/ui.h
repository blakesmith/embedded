#ifndef KEEBIRD_UI_H_
#define KEEBIRD_UI_H_

#include <cstdint>

#include "x11_display.h"

namespace keebird {

class Ui {
public:
    Ui(const uint16_t display_width,
       const uint16_t display_height);

    ~Ui() = default;

    int Init();
    void Stop();

private:
    X11Display display_;
};

}

#endif
