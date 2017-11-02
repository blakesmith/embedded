licenses(["unencumbered"])

cc_library(
    name = "stm_cmsis",
    hdrs = glob(["CMSIS/Include/*.h"]),
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_cmsis_device",
    hdrs = glob(["CMSIS/Device/ST/STM32F4xx/Include/*.h"]),
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_std_periph",
    srcs = glob(["STM32F4xx_StdPeriph_Driver/src/*.c"]),
    hdrs = glob(["STM32F4xx_StdPeriph_Driver/inc/*.h"]),
    copts = [
        "-Ithird_party/STM/CMSIS/Include",
        "-Ithird_party/STM/CMSIS/Device/ST/STM32F4xx/Include",
        "-Ithird_party/STM/STM32F4xx_StdPeriph_Driver/inc",
        "-include third_party/STM/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_conf.h",
        "-DSTM32F411xE"
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":stm_cmsis",
        ":stm_cmsis_device"
    ]
)

