#include "ui.h"

namespace clock {

UI::UI(Display7Seg* display)
    : display_(display)
{ }

void UI::Clear() {
    display_->Clear();
}

void UI::ToggleColon(bool on) {
    display_->ToggleColon(on);
}

void UI::SetHour(uint8_t hour) {
    display_->SetNumber(0, hour, 2, false);
}

void UI::SetMinute(uint8_t minute) {
    display_->SetNumber(3, minute, 2, true);
}

void UI::Update() {
    display_->WriteDisplay();
}

}
