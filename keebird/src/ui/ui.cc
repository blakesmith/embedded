#include "ui.h"

namespace keebird {

Ui::Ui(const uint16_t display_width,
       const uint16_t display_height)
    : display_(display_width, display_height),
      last_input_event_(InputEventType::NONE)
{ }

int Ui::Start() {
    return display_.Start();
}

void Ui::Stop() {
    display_.Stop();
}

InputEvent Ui::Poll() {
    InputEvent event = display_.Poll();
    if (event == last_input_event_) {
        return InputEvent(InputEventType::NONE);
    } else {
        last_input_event_ = event;
        return event;
    }
}

}
