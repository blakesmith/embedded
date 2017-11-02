cc_library(
    name = "stm_drivers_breadboard",
    srcs = glob(["src/*.cc"]),
    hdrs = glob(["src/*.h"]),
    copts = [
        "-fno-rtti",
        "-Ithird_party/STM/CMSIS/Include",
        "-Ithird_party/STM/CMSIS/Device/ST/STM32F4xx/Include",
        "-Ithird_party/STM/STM32F4xx_StdPeriph_Driver/inc",
        "-DSTM32F411xE"
    ],
    deps = [
        "//third_party/STM:stm_cmsis",
        "//third_party/STM:stm_cmsis_device",
        "//third_party/STM:stm_std_periph_breadboard"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_drivers_prototype",
    srcs = glob(["src/*.cc"]),
    hdrs = glob(["src/*.h"]),
    copts = [
        "-fno-rtti",
        "-Ithird_party/STM/CMSIS/Include",
        "-Ithird_party/STM/CMSIS/Device/ST/STM32F4xx/Include",
        "-Ithird_party/STM/STM32F4xx_StdPeriph_Driver/inc",
        "-DSTM32F413_423xx"
    ],
    deps = [
        "//third_party/STM:stm_cmsis",
        "//third_party/STM:stm_cmsis_device",
        "//third_party/STM:stm_std_periph_breadboard"
    ],
    visibility = ["//visibility:public"]
)

