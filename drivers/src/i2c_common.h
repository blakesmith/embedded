#include "stm32f4xx_i2c.h"

#define I2C_WAIT_FOR_EVENT(E) {                     \
        while (!I2C_CheckEvent(I2Cx, E));       \
    }

#define I2C_WAIT_FOR_FLAG(F) {                  \
        while (I2C_GetFlagStatus(I2Cx, F)); \
    }

