licenses(["unencumbered"])

cc_library(
    name = "stm_cmsis",
    hdrs = glob(["CMSIS/Include/*.h"]),
    strip_include_prefix = "CMSIS/Include/",
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_cmsis_device",
    hdrs = glob(["CMSIS/Device/ST/STM32F4xx/Include/*.h"]),
    strip_include_prefix = "CMSIS/Device/ST/STM32F4xx/Include/",
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_std_periph",
    srcs = glob(["STM32F4xx_StdPeriph_Driver/src/*.c"]),
    hdrs = glob(["STM32F4xx_StdPeriph_Driver/inc/*.h"]),
    strip_include_prefix = "STM32F4xx_StdPeriph_Driver/inc/",
    copts = [
        "-include stm32f4xx_conf.h",
    ] + select({
        ":target_breadboard": ["-DSTM32F411xE"],
        ":target_prototype": ["-DSTM32F413_423xx"]
    }),
    visibility = ["//visibility:public"],
    deps = [
        ":stm_cmsis",
        ":stm_cmsis_device"
    ]
)

config_setting(
    name = "target_breadboard",
    values = {
        "define": "TARGET=breadboard"
    }
)

config_setting(
    name = "target_prototype",
    values = {
        "define": "TARGET=prototype"
    }
)
