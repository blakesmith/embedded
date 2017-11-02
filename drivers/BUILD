cc_library(
    name = "stm_drivers",
    srcs = glob(["src/*.cc"]),
    hdrs = glob(["src/*.h"]),
    copts = [
        "-Ithird_party/STM/CMSIS/Include",
        "-Ithird_party/STM/CMSIS/Device/ST/STM32F4xx/Include",
        "-Ithird_party/STM/STM32F4xx_StdPeriph_Driver/inc",
        "-DSTM32F411xE"
    ],
    deps = [
        "//third_party/STM/CMSIS:stm_cmsis",
        "//third_party/STM/CMSIS/Device/ST/STM32F4xx:stm_cmsis_device",
        "//third_party/STM:stm_std_periph"
    ],
    visibility = ["//visibility:public"]
)
