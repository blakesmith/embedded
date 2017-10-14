#ifndef NOME_USER_INTERFACE_H_
#define NOME_USER_INTERFACE_H_

#include "pec11_renc.h"
#include "ht16K33_display.h"
#include "status_led.h"
#include "settings.h"

namespace nome {

class UserInterface {

public:
    UserInterface(Settings& settings);
    ~UserInterface() = default;
    
    void Init();
    void SetOk(bool ok);
    bool Update();
    void RefreshDisplay();

private:
    StatusLed status_led_;
    Pec11RotaryEncoder knob_;
    HT16K33Display display_;

    long knob_offset_;
    Settings& settings_;
};
    
}

#endif
