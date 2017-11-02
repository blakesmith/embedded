licenses(["unencumbered"])

cc_library(
    name = "stm_std_periph",
    srcs = glob(["STM32F4xx_StdPeriph_Driver/src/*.c"]),
    hdrs = glob(["STM32F4xx_StdPeriph_Driver/inc/*.h"]),
    copts = [
        "-Ithird_party/STM/CMSIS/Include",
        "-Ithird_party/STM/CMSIS/Device/ST/STM32F4xx/Include",
        "-Ithird_party/STM/STM32F4xx_StdPeriph_Driver/inc",
        "-DSTM32F411xE"
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//third_party/STM/CMSIS:stm_cmsis",
        "//third_party/STM/CMSIS/Device/ST/STM32F4xx:stm_cmsis_device"
    ]
)
