cc_library(
    name = "stm32_drivers_breadboard",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    copts = [
        "-fno-rtti",
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
    name = "stm32_drivers_prototype",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    copts = [
        "-fno-rtti",
        "-DSTM32F413_423xx"
    ],
    deps = [
        "//third_party/STM:stm_cmsis",
        "//third_party/STM:stm_cmsis_device",
        "//third_party/STM:stm_std_periph_breadboard"
    ],
    visibility = ["//visibility:public"]
)

