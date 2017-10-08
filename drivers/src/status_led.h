#ifndef STATUS_LED_H_
#define STATUS_LED_H_

class StatusLed {
public:
    void Init();
    void ToggleOk();
    void ToggleError();
    void ToggleActivity();
    void SetOk(bool on);
    void SetError(bool on);
    void SetActivity(bool on);
};

#endif
