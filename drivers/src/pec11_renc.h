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
    bool GetAndClearButtonPressed();
    
private:
    EncoderAction lookup_action();
    void setup_clockwise();
    void setup_counter_clockwise();
    void setup_button();

    volatile uint8_t encoder_state_;
    volatile long encoder_count_;
    volatile bool button_pressed_;
};

#endif
