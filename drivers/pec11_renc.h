#ifndef PEC11_RENC_H_
#define PEC11_RENC_H_

#include "gpio_pin.h"

enum RotationAction {
    ENC_ACTION_NONE = 0,
    ENC_ACTION_ROTATE_CLOCKWISE = 1,
    ENC_ACTION_ROTATE_COUNTER_CLOCKWISE = -1
};

enum ButtonAction {
    BUTTON_ACTION_NONE,
    BUTTON_ACTION_DOWN,
    BUTTON_ACTION_UP
};

class Pec11RotaryEncoder {

public:
    Pec11RotaryEncoder(GPIOPin& clockwise_pin,
                       GPIOPin& counter_clockwise_pin,
                       GPIOPin& button_pin);
    ~Pec11RotaryEncoder() = default;
    void Init();
    void ResetCount();
    void ReadState();
    long GetCount();
    ButtonAction GetButtonAction();
    
private:
    RotationAction rotation_action(uint32_t pin_state);
    ButtonAction button_action(uint32_t pin_state);

    GPIOPin& clockwise_pin_;
    GPIOPin& counter_clockwise_pin_;
    GPIOPin& button_pin_;

    uint8_t rotation_state_;
    uint8_t button_state_;
    
    long encoder_count_;
    ButtonAction button_action_;
};

#endif
