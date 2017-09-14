#ifndef PEC11_RENC_H_
#define PEC11_RENC_H_

enum EncoderAction {
    ENC_ACTION_NONE,
    ENC_ACTION_ROTATE_CLOCKWISE,
    ENC_ACTION_ROTATE_COUNTER_CLOCKWISE,
    ENC_ACTION_PUSH_BUTTON
};

enum PinState {
    PIN_STATE_HIGH,
    PIN_STATE_LOW
};

class Pec11RotaryEncoder {

public:
    Pec11RotaryEncoder();
    ~Pec11RotaryEncoder() = default;
    void Init();
    EncoderAction GetAction();
private:
    PinState cw_pin_state_;
    PinState ccw_pin_state_;
    PinState button_pin_state_;

    PinState read_pin_state(uint32_t idr);
};

#endif
