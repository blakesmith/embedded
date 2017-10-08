#ifndef STATUS_LED_H_
#define STATUS_LED_H_

class StatusLed {
public:
    void Init();
    void ToggleOk();
    void ToggleError();
    void SetOk(bool on);
    void SetError(bool on);
};

#endif
