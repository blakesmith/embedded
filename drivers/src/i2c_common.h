#include "stm32f4xx_i2c.h"

#define I2C_WAIT_FOR_EVENT(I, E) {            \
        while (!I2C_CheckEvent(I, E));       \
    }

#define I2C_WAIT_FOR_FLAG(I, F) {        \
        while (I2C_GetFlagStatus(I, F)); \
    }

