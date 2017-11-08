cc_library(
    name = "stm32",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    copts = select({
        ":target_breadboard": [
            "-fno-rtti",
            "-DSTM32F411xE"
        ],
        ":target_prototype": [
            "-fno-rtti",
            "-DSTM32F413_423xx"
        ]
    }),
    deps = [
        "//third_party/STM:stm_cmsis",
        "//third_party/STM:stm_cmsis_device",
        "//third_party/STM:stm_std_periph"
    ],
    visibility = ["//visibility:public"]
)

config_setting(
    name = "target_breadboard",
    define_values = {
        "TARGET": "breadboard"
    }
)

config_setting(
    name = "target_prototype",
    define_values = {
        "TARGET": "prototype"
    }
)
