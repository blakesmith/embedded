#include "ui.h"

namespace keebird {

Ui::Ui(const uint16_t display_width,
       const uint16_t display_height)
    : display_(display_width, display_height)
{ }

int Ui::Start() {
    return display_.Start();
}

void Ui::Stop() {
    display_.Stop();
}

InputEvent Ui::Poll() {
    return display_.Poll();
}

}
