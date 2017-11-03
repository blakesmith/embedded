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

COMMON_COPTS = [
    "-include stm32f4xx_conf.h",
]

cc_library(
    name = "stm_std_periph_breadboard",
    srcs = glob(["STM32F4xx_StdPeriph_Driver/src/*.c"]),
    hdrs = glob(["STM32F4xx_StdPeriph_Driver/inc/*.h"]),
    strip_include_prefix = "STM32F4xx_StdPeriph_Driver/inc/",
    copts = COMMON_COPTS + [
        "-DSTM32F411xE"
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":stm_cmsis",
        ":stm_cmsis_device"
    ]
)

cc_library(
    name = "stm_std_periph_prototype",
    srcs = glob(["STM32F4xx_StdPeriph_Driver/src/*.c"]),
    hdrs = glob(["STM32F4xx_StdPeriph_Driver/inc/*.h"]),
    strip_include_prefix = "STM32F4xx_StdPeriph_Driver/inc/",
    copts = COMMON_COPTS + [
        "-DSTM32F413_423xx"
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":stm_cmsis",
        ":stm_cmsis_device"
    ]
)

