licenses(["unencumbered"])

cc_library(
    name = "stm_cmsis",
    hdrs = glob(["CMSIS/Include/*.h"]),
    strip_include_prefix = "CMSIS/Include/",
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_cmsis_device",
    hdrs = glob(["CMSIS/Device/ST/STM32F0xx/Include/*.h"]),
    strip_include_prefix = "CMSIS/Device/ST/STM32F0xx/Include/",
    visibility = ["//visibility:public"]
)
