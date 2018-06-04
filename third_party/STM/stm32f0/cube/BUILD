licenses(["unencumbered"])

cc_library(
    name = "base",
    hdrs = [
        "Inc/stm32f0xx_hal.h",
        "Inc/stm32f0xx_hal_conf.h",
        "Inc/stm32f0xx_hal_def.h",
        "Inc/stm32f0xx_hal_flash.h",
        "Inc/stm32f0xx_hal_flash_ex.h",
        "Inc/stm32f0xx_hal_gpio.h",
        "Inc/stm32f0xx_hal_gpio_ex.h",
        "Inc/stm32f0xx_ll_gpio.h",
        "Inc/stm32f0xx_hal_rcc.h",
        "Inc/stm32f0xx_hal_rcc_ex.h",
        "Inc/stm32f0xx_ll_rcc.h",
    ],
    srcs = [
        "Src/stm32f0xx_hal_gpio.c",
        "Src/stm32f0xx_ll_gpio.c",
        "Src/stm32f0xx_hal_rcc.c",
        "Src/stm32f0xx_ll_rcc.c",
    ],
    deps = [
        "//third_party/STM/stm32f0:stm_cmsis",
        "//third_party/STM/stm32f0:stm_cmsis_device",
    ],
    copts = [
        "-DSTM32F042x6"
    ],
    strip_include_prefix = "Inc/",
    visibility = ["//visibility:public"]
)
