#ifndef PEC11_RENC_H_
#define PEC11_RENC_H_

enum EncoderAction {
    ENC_ACTION_NONE,
    ENC_ACTION_ROTATE_CLOCKWISE,
    ENC_ACTION_ROTATE_COUNTER_CLOCKWISE
};

class Pec11RotaryEncoder {

public:
    Pec11RotaryEncoder();
    ~Pec11RotaryEncoder() = default;
    void Init();
    void HandleInterrupt();
    EncoderAction GetAction();
    long GetCount();
private:
    EncoderAction lookup_action();
    void disable_irq();
    void enable_irq();
    void setup_clockwise();
    void setup_counter_clockwise();

    volatile uint8_t encoder_state_;
    volatile long encoder_count_;
};

#endif
