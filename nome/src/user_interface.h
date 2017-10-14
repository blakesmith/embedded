#ifndef NOME_USER_INTERFACE_H_
#define NOME_USER_INTERFACE_H_

#include "pec11_renc.h"
#include "ht16K33_display.h"
#include "status_led.h"

namespace nome {

class UserInterface {

public:
    void Init();
    void SetOk(bool ok);

private:
    Pec11RotaryEncoder knob;
    HT16K33Display display;
    StatusLed status_led;

};
    
}

#endif
