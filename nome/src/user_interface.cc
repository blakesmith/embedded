#include "user_interface.h"

namespace nome {

void UserInterface::Init() {
    // display.Init();
    // knob.Init();
    status_led.Init();
}

void UserInterface::SetOk(bool ok) {
    status_led.SetOk(ok);
}

}
