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
private:
    EncoderAction lookup_action();
    void setup_clockwise();
    void setup_counter_clockwise();

    volatile uint8_t encoder_state_;
    volatile long encoder_count_;
};

#endif
