licenses(["unencumbered"])

cc_library(
    name = "common_bin",
    srcs = [
        "startup_stm32f042x6.s",
        "system_stm32f0xx.c",
    ],
    hdrs = [
        "system_stm32f0xx.h",
    ],
    deps = [
        "//third_party/STM/stm32f0:stm_cmsis",
        "//third_party/STM/stm32f0:stm_cmsis_device"
    ],
    copts = [
        "-DSTM32F042x6"
    ],
    visibility = ["//visibility:public"]
)
