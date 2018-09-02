#include "ui.h"

namespace keebird {

Ui::Ui(const uint16_t display_width,
       const uint16_t display_height)
    : display_(display_width, display_height)
{ }

int Ui::Init() {
    return display_.Init();
}

void Ui::Stop() {
    display_.Stop();
}

}
