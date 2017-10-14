#ifndef PEC11_RENC_H_
#define PEC11_RENC_H_

enum EncoderAction {
    ENC_ACTION_NONE = 0,
    ENC_ACTION_ROTATE_CLOCKWISE = 1,
    ENC_ACTION_ROTATE_COUNTER_CLOCKWISE = -1
};

class Pec11RotaryEncoder {

public:
    Pec11RotaryEncoder();
    ~Pec11RotaryEncoder() = default;
    void Init();
    void HandleInterrupt();
    long GetCount();
    void ResetCount();
    void ReadState();
    bool GetAndClearButtonPressed();
    
private:
    EncoderAction lookup_action(uint32_t pin_state);

    uint8_t encoder_state_;
    long encoder_count_;
    bool button_pressed_;
};

#endif
